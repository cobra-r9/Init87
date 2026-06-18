---
title: "'fopen' File Not Found Error"
description: "To get a grasp of what is actually happening under the fopen function, I did some research, web searchs and AI analysis and wrote why this error occured."
type: error
tags: [perror, stdio]
---

## fopen and analysis

**Here is the exact code what I wrote : **

<gh-include src="cobra-r9/Init87/main/misc/stdio/errors/fopen.c"></gh-include>


## The call chain (top to bottom)

Given below is the exact call chain top to bottom of what is happening when fopen is called. glibc is doing some sort of `__fopen_internal` wrapper call (I don't know what it actually means, yet that is some kind of function wrapper (see below)). Which then invokes the `_IO_file_fopen()`, which in turn calls `_IO_file_open()`, which then calls the actual linux syscall : `open()`.

```
fopen("file-not-exist.c", "r")
  └─ glibc: __fopen_internal()          [libio/iofopen.c]
       └─ _IO_file_fopen()              [libio/fileops.c]
            └─ _IO_file_open()
                 └─ open() / openat()   ← actual Linux syscall
                      └─ kernel: do_sys_openat2()
                           └─ do_filp_open()
                                └─ path_openat()
                                     └─ lookup_open()
                                          └─ returns -ENOENT
```


### 1. glibc's `fopen` internals

`fopen` is a thin wrapper around `__fopen_internal`:

And actually - it is not `__fopen_internal` serving as a wrapper for `fopen`, but it is the reverse. And that one is located in the `libio/iofopen.c`. Below given is the simplified version of that underlying function. 

```c
// libio/iofopen.c (simplified)
FILE *
__fopen_internal(const char *filename, const char *mode, int is32) {
    struct locked_FILE {
        struct _IO_FILE_plus fp;
        // ...
    } *new_f = malloc(sizeof(*new_f));  // heap-allocates the FILE struct

    _IO_init_internal(&new_f->fp.file, 0);
    _IO_JUMPS(&new_f->fp) = &_IO_file_jumps;
    _IO_file_init_internal(&new_f->fp);

    if (_IO_file_fopen(&new_f->fp.file, filename, mode, is32) == NULL) {
        // ← on failure, reaches here
        _IO_un_link(&new_f->fp);   // unlink from glibc's internal FILE list
        free(new_f);               // free the heap allocation
        return NULL;               // ← this NULL is what you check
    }
    // ...
}
```

So `fopen` has already done a `malloc` and `free` behind our back before returning `NULL`. The `FILE *` we receive as `NULL` means the whole allocation was torn down already. It is clear that : this fopen internal function is heap allocating the file struct. Then it does something sort of initialisation. We should not be worrying about what is happening here right now, yet this is the overall structure. The `malloc` and `free` are done by this function and that is where the `NULL` is from. 


### 2. The syscall: `openat2` and the kernel path

`_IO_file_open` eventually issues `openat(AT_FDCWD, "file-not-exist.c", O_RDONLY)`.

And you know, FDCWD is nothing but the file descriptor of the current working directory and it is going to do everything relative to (AT) the current working directory. So if it needs to look for a file called `file-not-exist.c`, it is going to look at the current working directory's `fd`. This is because we need not go through the hassle of opening a directory to get a real descriptor. Instead we pass this `AT_FDCWD` - and the kernel says 'Ok, I will just use the process's current working directory instead'.

Inside the kernel (`fs/open.c`):

```
do_sys_openat2()
  └─ build_open_flags()        // parses O_RDONLY → no O_CREAT flag
  └─ do_filp_open()
       └─ path_openat()
            └─ link_path_walk() // walks the directory path component by component
            └─ do_last()
                 └─ lookup_open()
                      └─ dir->i_op->lookup() // hits the filesystem's VFS lookup
                           └─ file not in dentry cache, not on disk
                           └─ returns ERR_PTR(-ENOENT)
```

Since `O_CREAT` isn't set (we opened with `"r"`, see the working code for flag table), `lookup_open` doesn't attempt to create the file. It finds nothing and returns `-ENOENT` (error, no entry). This propagates all the way back to the syscall return value as `-2`. Don't worry for now, all we need to see is that `return ERR_PTR(-ENOENT)`. It kinda looks in the dentry cache, if it is not in the dentry cache, it looks if it is in the disk. Dentry cache is just the relationship data. For example in the directory `example`, we have a file `file.txt`, then the dentry cache just remembers that the parent folder `example` has a file called `file.txt` which has an inode number(search web and learn) `#2390`. And here our `file-not-exist.txt` does not have a cached entry in the `dentry` tree, it would do a long process of looking in the actual disk. If not found there too, then it does the `ENOENT`. (that is -ENOENT).


### 3. How `errno` gets set — the glibc syscall wrapper

Claude says that this is the part most people don't think about. The raw Linux syscall returns a negative number on error. glibc's syscall wrapper (generated via `sysdeps/unix/sysv/linux/` macros) does the following.:

```c
// Conceptually what the wrapper does:
long ret = syscall(SYS_openat, AT_FDCWD, path, flags, mode);
if (ret < 0) {
    errno = -ret;   // errno = -(-2) = 2 = ENOENT
    return -1;
}
return ret;
```

`errno` itself is **not** a plain global. In glibc it's a macro:

```c
// include/errno.h (glibc)
#define errno (*__errno_location())
```

`__errno_location()` returns a **thread-local pointer** — each thread has its own `errno`. This is why errno is safe in multithreaded code as long as you read it before your next syscall.

`ENOENT` is defined as:

```c
// include/uapi/asm-generic/errno-base.h (kernel UAPI, mirrored in glibc)
#define ENOENT   2   /* No such file or directory */
```


### 4. `perror` internals

```c
// stdio-common/perror.c (glibc, simplified)
void perror(const char *s) {
    int errnum = errno;                    // capture errno immediately
    const char *msg = strerror(errnum);   // look up string for errno=2
    // prints to stderr: "fopen failed! figure out why.: No such file or directory\n"
    if (s != NULL && *s != '\0')
        fprintf(stderr, "%s: %s\n", s, msg);
    else
        fprintf(stderr, "%s\n", msg);
}
```

`strerror(2)` indexes into an internal string table. For `ENOENT = 2` you get `"No such file or directory"` — this string lives in glibc's read-only data segment.

**Important:** `perror` captures `errno` at call time. If you called any other function between `fopen` and `perror`, `errno` could have been overwritten. Your code is correct — you check `!file` and immediately call `perror`.


### Full picture as a diagram

```
fopen("file-not-exist.c", "r")
│
├─ malloc()  ← allocates _IO_FILE_plus on heap
│
├─ openat(AT_FDCWD, path, O_RDONLY)  ← syscall
│     kernel returns: -2  (i.e. -ENOENT)
│     glibc wrapper: errno = 2, returns -1
│
├─ _IO_file_fopen sees -1 → failure
├─ free() + _IO_un_link()
└─ returns NULL
         │
         ▼
  if (!file) → true
         │
         ▼
  perror(...)
    errno = 2
    strerror(2) → "No such file or directory"
    write to stderr fd(2):
    "fopen failed! figure out why.: No such file or directory"
```


### Reference links

| What | Where |
|---|---|
| glibc `fopen` source | https://sourceware.org/git/?p=glibc.git;a=blob;f=libio/iofopen.c |
| glibc `_IO_file_open` | https://sourceware.org/git/?p=glibc.git;a=blob;f=libio/fileops.c |
| Linux `do_sys_openat2` | https://elixir.bootlin.com/linux/latest/source/fs/open.c |
| `ENOENT` kernel definition | https://elixir.bootlin.com/linux/latest/source/include/uapi/asm-generic/errno-base.h |
| `errno` man page | https://man7.org/linux/man-pages/man3/errno.3.html |
| `fopen` man page | https://man7.org/linux/man-pages/man3/fopen.3.html |
| `perror` man page | https://man7.org/linux/man-pages/man3/perror.3.html |


**TL;DR:** `fopen` → `openat` syscall → kernel can't find the inode → returns `-ENOENT` → glibc negates it into `errno = 2` → `fopen` returns `NULL` → `perror` reads `errno`, calls `strerror(2)`, writes the human-readable string to stderr.

## The corrected code. 

**just open a file which exists, or use a `r+`** mode. 

<gh-include src="cobra-r9/Init87/main/misc/stdio/fopen.c"></gh-include>

