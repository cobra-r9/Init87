---
title: "A bug or something? - fwrite failed."
description: "This is where most class of other bugs appear. When we miss something very small in the logic. And this page will explain what it is."
type: error
tags: [perror, stdio, fwrite]
---

# fwrite and my code 

**Here is the exact code what I wrote :**

we may try to figure out what the error is in this code. Why did my `fwrite` produce error stating `Success`.

<gh-include src="cobra-r9/Init87/main/misc/stdio/errors/fwrite.c"></gh-include>

## What fwrite actually is?

Below given is the function signature of `fwrite` - i.e, it's declaration. 

```c 
size_t fwrite(const void *prt, size_t size, size_t nmemb, FILE *stream);
```

It doesn't write **size bytes** - it writes `nmemb` elements, each `size` bytes wide. Internally it treats the memory block as `size *count` bytes and write them sequentially as if calling `fputc` for each byte. The return value is not a byte count - it's the number of complete elements successfully written. If that returned count is less than the `nmemb`, a writing error prevented completion and the stream's error indicator (not `errno`) gets set. 

> It is important for us to note that **`errno` may or may not be set**, but it is the **error indicator** of the stream that is get set. Stream? What stream? the FILE stream. It is a struct which has all this relevant field for setting errors. And this error can be **accessed via `ferror`**.

Therefore, the *idiomatic* check is `ferror(stream)`, not just comparing the return value. That is why I added the *comparison* alongside the `ferror` check and it turns out the actual bug was in that comparison. `ferror` was not set. It is good to go with `ferror` alone for most cases. But if you know for sure that - *The exact number of nmemb are the ones written and you are comparing them*. So remember that `ferror` is the one that actually is gonna tell us whether it is actually an error vs (size of nmemb being zero for example.)

## What exactly is happening under hood 

Here we are stepping into the `glibc` part. Though I did not completely grasp everything I referred and needed at least some intermediate knowledge in the **syscall territory**, as far as I can explain in understandable words :

> We should note this : As soon as we call the `fwrite` - **it is not going to do some magic to write directly to our disks.** It follows a sequence of steps as shown below. 

1) `fwrite` will be calling `_IO_fwrite`, just like that one in the `fopen`. Remember? `_IO_fopen`. This is the glibc's internal entry point. It is going to compute the total byte count (that is `size` * `nmemb`) and **hands it to stream's write logic.**

2) **Copy into the `FILE's` internal buffer** : That is every `FILE*` has a `_IO_FILE` struct with buffer pointers(`_IO_write_ptr`, `_IO_write_base`, `_IO_write_end`). If the data fits in the remaining buffer space, `fwrite` is literally just a `memcpy` into that buffer. No syscall happens. Our 8 bytes against a buffer size of several KB never leave the userspace at this point. But when does the syscall happen?

3) **Buffering mode decides when a syscall happens.** A stream opened on a regular file with `fopen` is fully buffered by default - that is characters are transmitted to the file in blocks of arbitrary size. The buffer actually gets flushed to the file (that is the data is written to the disck) only when the file fills up or when the stream is closed, or when the program exits normally. Everything, else - stays as a buffer. 

4) **The syscall at the final moment :** `fclose` calls `_IO_file_close_it`, which calls the `_IO_do_write`, which calls the actual `write` syscall, copying the buffer to the kernel's page cache. This is the point where a real I/O error (disk full, EROFS, quota, etc.) could occur. 

So in our program: `fwrite` succeeded the instant the `memcpy` into the buffer completed. There was never a real chance for it to fail with 18 bytes into an empty buffer.

## what actually is the bug?

```c
int return_value = fwrite(buffer, sizeof(buffer[0]), countof(buffer) - 1, file);
// we write 18 elements (countof(buffer) - 1 = 19 - 1 = 18)

if (ferror(file) || (unsigned long)return_value < countof(buffer)) {
//                                                 ^^^^^^^^^^^^^^^ 19, not 18!
```

Walk through it with real numbers:

- `countof(buffer)` = 19 (array size, includes the `\0`)
- I correctly write `countof(buffer) - 1` = **18** elements
- `fwrite` succeeds completely → `return_value` = **18**
- `ferror(file)` → false (nothing actually failed)
- Second condition: `18 < 19` → **true**

So basically I was comparing what I *actually asked fwrite to write* (18) against the *full array size including the null terminator* (19) — two different numbers that were never supposed to be compared. The `-1` correction I applied to the `fwrite` call needed to be mirrored in the comparison too. It wasn't. So the `if` triggers even on a flawless write - that is my comparison was always true, no matter.

**Why the error message says "Success":** `errno` is only ever *set* by a failing call — no library function is required to clear or set it on success. `fwrite` succeeded, so it never touched `errno`. It was last explicitly set to `0` by me, and `fopen` succeeding didn't change it either. So when `perror("fwrite failed.")` runs, it calls `strerror(errno)` on `errno == 0`, and POSIX defines that string as `"Success"`. The program is confidently reporting an error that the OS insists never happened — because, mechanically, it didn't.

## The fix

```c
if (ferror(file) || (size_t)return_value < countof(buffer) - 1) {
```

Compare against the same `-1`-adjusted value that I actually requested.

**One more smell, unrelated to this bug but worth fixing (this is by claude - to me):** `fwrite` returns `size_t`, but you're storing it in `int`. It works here only because 18 is tiny. On a large write (`nmemb` > `INT_MAX`, or just on a platform/ABI where the implicit conversion truncates oddly) this becomes a real bug. Declare it `size_t return_value` and drop the cast entirely — compare `size_t` to `size_t`.

## Reference table

| Topic | Source |
|---|---|
| `fwrite` signature & return semantics | https://en.cppreference.com/w/c/io/fwrite |
| `fwrite` short-write / ferror contract | https://cplusplus.com/reference/cstdio/fwrite/ |
| glibc stream buffering concepts | https://www.gnu.org/software/libc/manual/html_node/Stream-Buffering.html |
| glibc buffer flushing rules | https://www.gnu.org/software/libc/manual/html_node/Flushing-Buffers.html |
| `errno`/`perror`/`strerror` man pages | https://man7.org/linux/man-pages/man3/errno.3.html |
| `write(2)` syscall | https://man7.org/linux/man-pages/man2/write.2.html |
| `_Countof`/`countof` proposal (note: this is a **C2y** proposal, not C23 — our file header is slightly off) | https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3369.pdf |
| Background on the `lengthof` → `countof` rename | https://thephd.dev/c2y-hitting-the-ground-running |


## The corrected code. 

**Add a symbol there - `fwrite` has been my favourite**

<gh-include src="cobra-r9/Init87/main/misc/stdio/fwrite.c"></gh-include>

