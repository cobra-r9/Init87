Now I have everything I need. Let me build the real master index.

---

# C File Manipulation — Master Index

---

## TIER 0 — Mental Model (Read First)

```
0.1  What a "file" is in Unix — everything is a file
0.2  The VFS (Virtual Filesystem Switch) — kernel abstraction layer
0.3  Inodes — what they store, what they don't
0.4  The file descriptor table — per-process, kernel, open file description
0.5  File descriptor vs. file description vs. FILE* — the three layers
0.6  The page cache — how the kernel buffers disk I/O
0.7  User-space buffering (stdio) vs. kernel buffering vs. raw disk
0.8  System call overhead — why buffering exists
0.9  errno — the global error variable, how it works, thread safety
0.10 The C standard vs. POSIX vs. Linux-specific — what's portable where
```

---

## TIER 1 — stdio Basics (`<stdio.h>`)

```
1.1   fopen / fclose — modes ("r","w","a","r+","w+","a+","rb","wb"...), return values
1.2   fopen failure — errno values, perror, strerror
1.3   The FILE* struct — what's inside, opaque type
1.4   Standard streams — stdin, stdout, stderr
1.5   fgetc / fputc — character I/O, why int not char, EOF sentinel
1.6   fgets / fputs — line I/O, null termination, newline behavior
1.7   fscanf / fprintf — formatted I/O, format string rules
1.8   fread / fwrite — binary block I/O, size vs count, partial returns
1.9   fseek / ftell — positioning, SEEK_SET, SEEK_CUR, SEEK_END
1.10  rewind — seek to 0 + clear error flag
1.11  feof / ferror / clearerr — error state flags
1.12  The feof-as-loop-condition bug — why it's wrong, correct pattern
1.13  fflush — flushing user-space buffer to kernel
1.14  Buffering modes — _IONBF, _IOLBF, _IOFBF, setvbuf, setbuf
1.15  The read/write switch rule — mandatory seek between r/w in "r+" mode
1.16  ungetc — pushing a character back into the stream
1.17  getchar / putchar / gets (dangerous) / puts
1.18  scanf family pitfalls — whitespace, %s buffer overflows, return value
1.19  printf family — sprintf, snprintf, vprintf, vasprintf
1.20  tmpfile / tmpnam — temporary file creation via stdio
1.21  freopen — reopen a stream to a different file (e.g. redirect stdout)
1.22  fwide — wide character mode on streams
```

---

## TIER 2 — POSIX Raw I/O (`<fcntl.h>` `<unistd.h>`)

```
2.1   open() — signature, return value, O_* flags overview
2.2   open() flags — O_RDONLY, O_WRONLY, O_RDWR
2.3   open() creation flags — O_CREAT, O_EXCL, O_TRUNC, O_APPEND
2.4   open() performance flags — O_DIRECT, O_SYNC, O_DSYNC, O_RSYNC
2.5   open() misc flags — O_NONBLOCK, O_NOCTTY, O_CLOEXEC, O_PATH
2.6   mode_t — permission bits when creating files, umask interaction
2.7   close() — return value matters, EINTR handling
2.8   read() — return values: 0=EOF, -1=error, n=bytes read
2.9   Partial reads — why read() returns less than requested
2.10  Reliable read loop — handling partial reads and EINTR
2.11  write() — partial writes, return value, write loop pattern
2.12  lseek() — off_t, return value, SEEK_SET/CUR/END
2.13  lseek() past EOF — creating sparse files
2.14  pread() / pwrite() — atomic offset+read, no seek side effects
2.15  readv() / writev() — scatter/gather I/O, struct iovec
2.16  dup() / dup2() / dup3() — duplicating file descriptors
2.17  fileno() — extracting fd from FILE*, mixing layers safely
2.18  fdopen() — wrapping a raw fd in a FILE*
2.19  pipe() / pipe2() — creating anonymous pipes
2.20  mkfifo() — named pipes (FIFOs)
2.21  creat() — historical shorthand for open() with O_CREAT|O_WRONLY|O_TRUNC
```

---

## TIER 3 — File Metadata & Filesystem Operations

```
3.1   stat() / fstat() / lstat() — the struct stat fields
3.2   struct stat fields — st_size, st_mode, st_ino, st_dev, st_nlink,
                           st_uid, st_gid, st_atime, st_mtime, st_ctime, st_blksize, st_blocks
3.3   File type macros — S_ISREG, S_ISDIR, S_ISLNK, S_ISCHR, S_ISBLK, S_ISFIFO, S_ISSOCK
3.4   Permission bit macros — S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP... S_ISUID, S_ISGID, S_ISVTX
3.5   access() — checking permissions before open (TOCTOU race, avoid)
3.6   faccessat() — access() relative to dirfd
3.7   chmod() / fchmod() — changing permissions
3.8   chown() / fchown() / lchown() — changing owner/group
3.9   umask() — default permission mask, process-wide, thread-unsafe
3.10  rename() / renameat() — atomic move/rename within a filesystem
3.11  unlink() — removing a filename (file deleted when all fds closed)
3.12  remove() — unlink for files, rmdir for dirs
3.13  link() — creating hard links
3.14  symlink() / readlink() / lstat() — symbolic links
3.15  realpath() — resolving symlinks to absolute path
3.16  truncate() / ftruncate() — changing file size, zeroing or shrinking
3.17  statvfs() / statfs() — filesystem statistics (free space, block size)
3.18  pathconf() / fpathconf() — filesystem limits per path
3.19  utime() / utimes() / utimensat() — modifying timestamps
3.20  sync() / fsync() / fdatasync() — flushing to physical disk
3.21  sync_file_range() — selective range flush (Linux-specific)
```

---

## TIER 4 — Directory Operations

```
4.1   opendir() / closedir() — opening a directory stream
4.2   readdir() — iterating entries, struct dirent
4.3   struct dirent fields — d_ino, d_name, d_type (not always reliable)
4.4   d_type values — DT_REG, DT_DIR, DT_LNK, DT_UNKNOWN
4.5   rewinddir() — resetting directory stream
4.6   telldir() / seekdir() — positioning in directory stream
4.7   mkdir() / mkdirat() — creating directories, mode bits
4.8   rmdir() — removing empty directories
4.9   getcwd() — current working directory
4.10  chdir() / fchdir() — changing working directory
4.11  Recursive directory traversal — building your own find(1)
4.12  nftw() — kernel-assisted tree walk, FTW_* flags
4.13  fts_open/fts_read/fts_close — BSD tree walk API (glibc has it)
4.14  openat() / unlinkat() / mkdirat() — fd-relative syscalls (avoid TOCTOU)
4.15  O_PATH file descriptors — lightweight reference to a path
4.16  /proc/self/fd — listing your own open file descriptors
4.17  /proc/self/fdinfo — fd details (offset, flags)
```

---

## TIER 5 — File Control & Descriptor Manipulation (`fcntl`)

```
5.1   fcntl() — overview, op codes
5.2   F_DUPFD / F_DUPFD_CLOEXEC — dup with minimum fd number
5.3   F_GETFD / F_SETFD — FD_CLOEXEC flag
5.4   F_GETFL / F_SETFL — open file status flags (O_APPEND, O_NONBLOCK...)
5.5   O_CLOEXEC — preventing fd leak across exec()
5.6   F_GETPIPE_SZ / F_SETPIPE_SZ — pipe capacity
5.7   F_NOTIFY — dnotify, directory change notifications (legacy, use inotify)
5.8   F_SETLEASE / F_GETLEASE — file lease notifications
5.9   F_GET_RW_HINT / F_SET_RW_HINT — I/O lifetime hints
5.10  ioctl() — device-specific control (not strictly file, but fd-based)
```

---

## TIER 6 — File Locking

```
6.1   Why locking — race conditions between processes
6.2   Advisory vs. mandatory locking — Linux advisory by default
6.3   flock() — whole-file BSD locking, LOCK_SH, LOCK_EX, LOCK_UN, LOCK_NB
6.4   fcntl() record locking — F_SETLK, F_SETLKW, F_GETLK, struct flock
6.5   struct flock fields — l_type, l_whence, l_start, l_len, l_pid
6.6   Read locks vs. write locks — sharing rules
6.7   Byte-range locking — locking specific regions of a file
6.8   Lock inheritance on fork() — child inherits fd, NOT locks
6.9   lockf() — POSIX simplified locking (wrapper over fcntl)
6.10  Lock file pattern — O_CREAT|O_EXCL atomic creation
6.11  PID lock files — /var/run/*.pid pattern
6.12  NFS locking — fcntl works, flock unreliable over NFS
6.13  Lock starvation and deadlock — detection, avoidance
6.14  open file description locks — OFD locks (Linux 3.15+, F_OFD_SETLK)
6.15  Mandatory locking — mount -o mand, largely broken/deprecated
```

---

## TIER 7 — Memory-Mapped Files (`mmap`)

```
7.1   What mmap does — mapping file into virtual address space
7.2   mmap() signature — addr, length, prot, flags, fd, offset
7.3   Protection flags — PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE
7.4   MAP_SHARED vs MAP_PRIVATE — visibility of changes, copy-on-write
7.5   MAP_ANONYMOUS — memory not backed by file
7.6   MAP_FIXED — force exact address (dangerous)
7.7   MAP_POPULATE — prefault pages into memory
7.8   MAP_LOCKED — prevent swapping (requires privilege)
7.9   MAP_HUGETLB — huge page mapping
7.10  MAP_NORESERVE — don't reserve swap space
7.11  munmap() — removing a mapping
7.12  mremap() — resize or move a mapping (Linux-specific)
7.13  msync() — flush mapping to file, MS_SYNC vs MS_ASYNC vs MS_INVALIDATE
7.14  mprotect() — changing protection of a region
7.15  madvise() — giving kernel hints, MADV_SEQUENTIAL, MADV_RANDOM,
                   MADV_WILLNEED, MADV_DONTNEED, MADV_FREE, MADV_HUGEPAGE
7.16  mincore() — querying which pages are in RAM
7.17  Page alignment requirements — offset must be page-aligned (getpagesize)
7.18  SIGBUS — what causes it in mmap'd context, handling
7.19  Advantages of mmap — zero-copy reads, no system call per access
7.20  Disadvantages of mmap — TLB pressure, minor faults, large files
7.21  mmap64 / _FILE_OFFSET_BITS=64 — large file support with mmap
7.22  Shared memory via mmap — IPC between processes
7.23  mmap vs read/write performance — when to use each
7.24  File-backed vs anonymous mappings — use cases
7.25  Mapping a file for read-only parsing — canonical pattern
7.26  Mapping a file for writing — ftruncate then mmap pattern
```

---

## TIER 8 — I/O Multiplexing & Event-Driven I/O

```
8.1   Blocking vs. non-blocking I/O — O_NONBLOCK, EAGAIN/EWOULDBLOCK
8.2   select() — watching fd sets, timeout, FD_* macros, fd_set limit (1024)
8.3   pselect() — select with signal mask atomicity
8.4   poll() — pollfd array, POLLIN/POLLOUT/POLLERR/POLLHUP, no fd limit
8.5   ppoll() — poll with signal mask
8.6   epoll — Linux-specific scalable I/O multiplexing
8.7   epoll_create1() — creating epoll instance, EPOLL_CLOEXEC
8.8   epoll_ctl() — EPOLL_CTL_ADD, EPOLL_CTL_MOD, EPOLL_CTL_DEL
8.9   epoll_wait() / epoll_pwait() — waiting for events, struct epoll_event
8.10  epoll events — EPOLLIN, EPOLLOUT, EPOLLERR, EPOLLHUP, EPOLLRDHUP, EPOLLPRI
8.11  Level-triggered vs. edge-triggered — EPOLLET, behavioral difference
8.12  EPOLLONESHOT — single-fire events
8.13  EPOLLEXCLUSIVE — avoiding thundering herd
8.14  epoll with regular files — not supported (always ready), use for sockets/pipes
8.15  select vs poll vs epoll — performance comparison, O(n) vs O(1)
8.16  kqueue (BSD) — equivalent to epoll on macOS/FreeBSD
8.17  eventfd() — userspace event notification fd (counters)
8.18  signalfd() — receiving signals via fd (epoll-compatible)
8.19  timerfd — timer expiry via fd
```

---

## TIER 9 — Asynchronous I/O

```
9.1   Synchronous vs. asynchronous I/O — conceptual difference
9.2   POSIX AIO — aio_read, aio_write, aio_fsync, aiocb struct
9.3   aio_return / aio_error — checking async operation status
9.4   aio_suspend — waiting for AIO completion
9.5   aio_cancel — cancelling in-flight AIO
9.6   POSIX AIO notification — SIGEV_SIGNAL, SIGEV_THREAD, SIGEV_NONE
9.7   Linux native AIO (libaio) — io_setup, io_submit, io_getevents
9.8   Limitations of Linux AIO — O_DIRECT only, no buffered support
9.9   io_uring — Linux 5.1+, ring buffer submission/completion queues
9.10  io_uring_setup / io_uring_enter — low-level interface
9.11  liburing — userspace library wrapping io_uring
9.12  io_uring SQE/CQE — submission queue entry, completion queue entry
9.13  io_uring features — IORING_FEAT_NODROP, IORING_FEAT_SUBMIT_STABLE
9.14  io_uring ops — IORING_OP_READ, IORING_OP_WRITE, IORING_OP_OPENAT, etc.
9.15  io_uring fixed buffers / registered files — reducing overhead
9.16  io_uring security concerns — kernel attack surface, Android disabled it
9.17  Thread-based async I/O — thread pool pattern (simplest approach)
```

---

## TIER 10 — Zero-Copy & High-Performance Transfers

```
10.1  sendfile() — kernel-to-kernel copy, no user-space buffer
10.2  sendfile() signature, offset handling, max size limits per call
10.3  splice() — zero-copy between two fds via kernel pipe buffer
10.4  tee() — copy between two pipes without consuming data
10.5  vmsplice() — moving user memory into a pipe
10.6  copy_file_range() — in-kernel file-to-file copy (Linux 4.5+)
10.7  O_DIRECT — bypassing page cache, alignment requirements (512/4096)
10.8  DMA and direct I/O — what O_DIRECT actually does
10.9  posix_fadvise() — access pattern hints to kernel
10.10 POSIX_FADV_SEQUENTIAL / RANDOM / WILLNEED / DONTNEED / NOREUSE / NORMAL
10.11 readahead() — Linux-specific prefetch (Linux-only)
10.12 posix_fallocate() — preallocating file space, preventing fragmentation
10.13 fallocate() — Linux-specific, FALLOC_FL_* flags (punch holes, keep size)
10.14 FALLOC_FL_PUNCH_HOLE — deallocating ranges in a file (zeroing disk blocks)
10.15 FALLOC_FL_KEEP_SIZE — preallocate without changing file size
10.16 ftruncate vs. fallocate — differences, sparse file behavior
10.17 I/O performance benchmarking — which method wins when
```

---

## TIER 11 — File Change Notification

```
11.1  inotify — Linux filesystem event notification API
11.2  inotify_init() / inotify_init1() — creating an inotify instance
11.3  inotify_add_watch() — registering path to watch
11.4  inotify_rm_watch() — removing a watch
11.5  struct inotify_event — wd, mask, cookie, len, name
11.6  inotify event masks — IN_CREATE, IN_DELETE, IN_MODIFY, IN_CLOSE_WRITE,
                              IN_MOVED_FROM, IN_MOVED_TO, IN_ATTRIB, IN_ALL_EVENTS
11.7  inotify cookies — correlating IN_MOVED_FROM and IN_MOVED_TO
11.8  inotify with epoll — the standard integration pattern
11.9  inotify limits — /proc/sys/fs/inotify/max_user_watches
11.10 inotify limitations — no network filesystem support, no recursive watches
11.11 Recursive inotify — building your own by watching each dir
11.12 fanotify — filesystem-wide notification (Linux 2.6.37+), requires CAP_SYS_ADMIN
11.13 fanotify vs inotify — scope, permissions, blocking events
11.14 dnotify — legacy directory notification via signals (deprecated, avoid)
11.15 kqueue (BSD) — equivalent on macOS/FreeBSD with EVFILT_VNODE
```

---

## TIER 12 — Sparse Files & Special File Features

```
12.1  Sparse files — holes, physical block allocation, apparent vs. real size
12.2  Creating sparse files — lseek past EOF then write
12.3  Detecting holes — SEEK_HOLE / SEEK_DATA (Linux 3.1+)
12.4  st_blocks vs st_size — why they differ for sparse files
12.5  cp --sparse — copying sparse files correctly
12.6  Sparse file use cases — VM disk images, database files, core dumps
12.7  Extended attributes (xattr) — metadata beyond stat
12.8  getxattr / setxattr / listxattr / removexattr
12.9  xattr namespaces — user., system., security., trusted.
12.10 File capabilities via xattr — security.capability
12.11 SELinux contexts via xattr — security.selinux
12.12 ACLs (Access Control Lists) — getfacl/setfacl, libacl
12.13 chattr / lsattr — immutable, append-only, nodump flags
12.14 ioctl(FS_IOC_GETFLAGS) — reading inode flags programmatically
12.15 File sealing (memfd) — F_SEAL_* flags, immutable memory
```

---

## TIER 13 — File Descriptors & Process Lifecycle

```
13.1  fd inheritance on fork() — child gets copy of fd table
13.2  fd sharing across fork — same open file description = shared offset
13.3  O_CLOEXEC — closing fds on exec(), avoiding leaks
13.4  FD_CLOEXEC via fcntl — same effect, two-step (non-atomic)
13.5  exec() family and files — open files persist unless FD_CLOEXEC
13.6  File descriptor limits — RLIMIT_NOFILE, getrlimit, setrlimit
13.7  /proc/sys/fs/file-max — system-wide fd limit
13.8  Enumerating open fds — /proc/self/fd, /proc/<pid>/fd
13.9  File descriptor passing over Unix sockets — SCM_RIGHTS, sendmsg/recvmsg
13.10 pidfd — file descriptors for processes (Linux 5.3+)
13.11 memfd_create() — anonymous file in RAM, no filesystem entry
13.12 O_TMPFILE — anonymous temp file, linkable later (Linux 3.11+)
13.13 Detecting fd leaks — valgrind, /proc/self/fd count
```

---

## TIER 14 — Temporary Files & Atomic Write Patterns

```
14.1  tmpfile() — anonymous temp file, auto-deleted on close
14.2  tmpnam() — just a name (racy, deprecated)
14.3  mkstemp() — safe temp file with unique name, returns fd
14.4  mkdtemp() — safe temp directory with unique name
14.5  mkostemp() — mkstemp with O_CLOEXEC, O_APPEND flags
14.6  The atomic write pattern — write to temp, then rename()
14.7  Why rename() is atomic — single filesystem only, single syscall
14.8  Crash-safe writes — fsync temp file before rename
14.9  O_TMPFILE pattern — Linux-specific anonymous file, then linkat()
14.10 Temp file directory selection — TMPDIR env, /tmp vs /var/tmp
14.11 Temp file cleanup — signal handlers, atexit(), unlink-on-open pattern
```

---

## TIER 15 — Synchronization & Durability

```
15.1  write() returns ≠ data on disk — the durability gap
15.2  fsync() — flush kernel buffers + disk cache (expensive)
15.3  fdatasync() — fsync without metadata (faster)
15.4  sync() — flush all kernel buffers system-wide
15.5  sync_file_range() — selective range flush, 4 flag modes
15.6  O_SYNC — synchronous writes per write() call
15.7  O_DSYNC — data-synchronous (like fdatasync per write)
15.8  Disk write cache — HDDs/SSDs cache writes, fsync forces flush
15.9  Write barriers — ensuring ordering (relevant for databases)
15.10 Journaling filesystems — ext4, XFS, how they affect durability
15.11 The durability cost — fsync() benchmarks, why databases struggle
```

---

## TIER 16 — Security & Permissions

```
16.1  Principle of least privilege — open with minimal flags
16.2  TOCTOU races — time-of-check-to-time-of-use, openat() solution
16.3  Symlink attacks — /tmp symlink races, O_NOFOLLOW
16.4  /proc/<pid>/fd symlink attacks
16.5  Securely creating files — O_CREAT|O_EXCL atomicity
16.6  Setuid/setgid on executables — how filesystem bits interact
16.7  umask and file creation security
16.8  File capabilities — CAP_DAC_READ_SEARCH, CAP_SYS_ADMIN, etc.
16.9  Landlock — user-space filesystem sandboxing (Linux 5.13+)
16.10 seccomp — syscall filtering for file-related calls
16.11 Chroot — filesystem root isolation, escape techniques
16.12 Detecting file tampering — inotify + hash verification
16.13 Safe path handling — avoiding path traversal (../ attacks)
```

---

## TIER 17 — Portability & Large File Support

```
17.1  off_t size — 32-bit systems, overflow on >2GB files
17.2  _FILE_OFFSET_BITS=64 — enabling 64-bit offsets on 32-bit systems
17.3  _LARGEFILE_SOURCE / _LARGEFILE64_SOURCE
17.4  fseeko() / ftello() — stdio equivalents using off_t
17.5  open64() / fopen64() / stat64() — explicit 64-bit variants
17.6  pread64() / pwrite64() — 64-bit offset variants
17.7  PATH_MAX — not reliable, handle dynamically
17.8  NAME_MAX — max filename length (255 on most filesystems)
17.9  POSIX vs Linux vs GNU extensions — what requires _GNU_SOURCE
17.10 macOS / BSD differences — no O_DIRECT, no sendfile() to non-sockets
17.11 Windows compatibility — no fds, HANDLE, CRLF line endings
17.12 Feature test macros — _POSIX_C_SOURCE, _XOPEN_SOURCE, _GNU_SOURCE
```

---

## TIER 18 — Error Handling Patterns

```
18.1  errno — meaning, when it's valid, stale values
18.2  perror() — printing errno description
18.3  strerror() / strerror_r() — thread-safe errno string
18.4  EINTR — signal interruption of syscalls, retry loops
18.5  EAGAIN / EWOULDBLOCK — non-blocking fd not ready
18.6  EIO — physical I/O error, drive failure
18.7  ENOSPC — disk full, partial writes
18.8  ENOMEM — allocation failures in I/O paths
18.9  EBADF — closed/invalid fd, double-close bugs
18.10 goto-cleanup pattern — single exit point with resource cleanup
18.11 Cleanup macros — DIE_IF(), GOTO_IF_ERR() patterns
18.12 defer pattern in C — macro-based cleanup (GCC cleanup attribute)
18.13 Checking fclose() — it can fail (buffered write failure)
18.14 Signal-safe I/O — async-signal-safe functions list
18.15 Error logging patterns — structured error context propagation
```

---

## TIER 19 — Practical Patterns & Idioms

```
19.1   Reading entire file into memory — fseek/ftell/fread pattern
19.2   Reading entire file with mmap — zero-copy alternative
19.3   Line-by-line processing without loading all into memory
19.4   Copying a file — read/write loop vs sendfile vs copy_file_range
19.5   Tail-following a file — inotify + lseek/read pattern
19.6   Parsing a binary format — struct overlay, endianness, alignment
19.7   Writing a binary format from scratch — versioned header design
19.8   Endianness — htonl/ntohl, htobe32/le32toh, portable byte order
19.9   Atomic counter file — read-modify-write with fcntl locking
19.10  Append-only log file — O_APPEND guarantees on local filesystems
19.11  Config file watcher — inotify + re-parse on IN_CLOSE_WRITE
19.12  Rolling log files — size check + rename + reopen pattern
19.13  Buffered reading with your own buffer — fread equivalent manually
19.14  Memory-mapped database file — mmap + msync + file lock pattern
19.15  Inter-process shared file — mmap MAP_SHARED + synchronization
19.16  Fast file existence check — stat() vs open() tradeoffs
19.17  Directory scanning for a pattern — opendir + readdir + fnmatch
19.18  Building a find(1) clone — recursive nftw + filter
19.19  Watching a directory tree recursively — inotify + auto-watch new dirs
19.20  Secure temp file with guaranteed cleanup — O_TMPFILE + linkat
19.21  File-based mutex — lock file pattern with PID validation
19.22  Writing a CSV parser — fgets + strtok/strsep
19.23  Writing a binary protocol parser — state machine over read()
19.24  Buffered output to file — write accumulate then flush pattern
19.25  Handling SIGPIPE — writing to closed pipe, SA_IGN or handle
```

---

## TIER 20 — Internals & Kernel Details (Deep Dive)

```
20.1  VFS layer — how every filesystem presents the same interface
20.2  Page cache internals — radix tree, dirty pages, writeback
20.3  Buffer cache vs page cache — historical, modern Linux merges them
20.4  How read() works end-to-end — syscall → VFS → fs → page cache → copy
20.5  How write() works end-to-end — copy → page cache → writeback → disk
20.6  I/O scheduler — deadline, CFQ, mq-deadline, BFQ, none (NVMe)
20.7  Direct I/O (O_DIRECT) internals — bypasses page cache, DMA directly
20.8  How mmap avoids copies — page table mapping into page cache
20.9  copy-on-write in MAP_PRIVATE — fork + mmap interaction
20.10 Huge pages — /proc/sys/vm/nr_hugepages, madvise MADV_HUGEPAGE
20.11 Transparent huge pages (THP) — automatic, madvise control
20.12 Filesystem-specific behaviors — ext4, XFS, Btrfs, tmpfs, procfs
20.13 /proc and /sys — pseudo-filesystems, no actual disk I/O
20.14 devtmpfs / udev — device files, major/minor numbers
20.15 FUSE — userspace filesystems, libfuse
20.16 overlayfs — union mounts (used by Docker)
20.17 Namespace filesystems — mount namespaces, pivot_root
20.18 io_uring internals — shared ring buffers, avoiding syscalls
```

---

## Quick Reference: Headers, Libraries, Compile Flags

```
stdio.h         — FILE*, fopen, fread, fprintf, fseek...
fcntl.h         — open, fcntl, O_* flags
unistd.h        — read, write, close, lseek, dup, access...
sys/stat.h      — stat, fstat, chmod, struct stat
sys/types.h     — off_t, pid_t, mode_t, dev_t
dirent.h        — opendir, readdir, struct dirent
sys/mman.h      — mmap, munmap, mprotect, msync, madvise
sys/file.h      — flock()
sys/inotify.h   — inotify_init, inotify_add_watch
sys/epoll.h     — epoll_create, epoll_ctl, epoll_wait
sys/sendfile.h  — sendfile()
sys/uio.h       — readv, writev, struct iovec
aio.h           — POSIX AIO (aio_read, aio_write...)
ftw.h           — nftw(), FTW_*
sys/xattr.h     — getxattr, setxattr, listxattr
sys/statvfs.h   — statvfs, struct statvfs

Compile flags:
  -D_FILE_OFFSET_BITS=64    large file support
  -D_POSIX_C_SOURCE=200809L POSIX.1-2008
  -D_GNU_SOURCE             all GNU/Linux extensions
  -luring                   for io_uring (liburing)
```

---

**193 topics across 20 tiers.** Want to go in order from Tier 0, or jump to a specific tier?


No. That index covers **file manipulation only**. C as a whole is an entirely different beast. And even within file manipulation, I left things out. Let me be straight about both:

---

**What's missing from the file manipulation index:**

- `fmemopen` / `open_memstream` — in-memory `FILE*` streams
- `getline` / `getdelim` — POSIX dynamic line reading
- `cookie I/O` — custom `FILE*` with your own read/write/seek/close hooks
- `ioprio_set` / `ioprio_get` — per-process I/O scheduling priority
- `FICLONE` / `FICLONERANGE` ioctl — btrfs/XFS reflinks (zero-cost file copies)
- `FIDEDUPERANGE` — block-level deduplication ioctl
- `fscrypt` — kernel filesystem encryption API
- `dm-verity` — block-level integrity verification
- FUSE / libfuse — writing your own filesystem in userspace
- `close_range()` — closing a range of fds atomically (Linux 5.9)
- `openat2()` — newer, stricter openat with resolve flags
- `pidfd_getfd()` — stealing an fd from another process
- `blkio` cgroup controller — I/O bandwidth throttling
- `/proc/sys/fs/*` tuning knobs
- `strace` / `ltrace` / `perf` / `blktrace` for I/O debugging
- `fio` / `iozone` benchmarking
- `libmagic` — file type detection (magic bytes)
- NFS-specific locking behavior
- `MS_SYNC` durability guarantees on different filesystems
- `O_PATH` fd operations in depth
- Write-ahead logging pattern (WAL)
- B-tree on a flat file — building a database from scratch
- Checksumming / integrity verification over file content
- Compression via `zlib` / `lz4` / `zstd` over file streams
- `/dev/null`, `/dev/zero`, `/dev/urandom` — special file behaviors

---

**And that index covers zero of actual C:**

File I/O is just one domain. C the language also encompasses:

- The full type system — integers, floats, pointers, arrays, structs, unions, bitfields, enums, qualifiers
- Undefined behavior — the entire minefield
- Memory management — `malloc`/`calloc`/`realloc`/`free`, `alloca`, arena allocators, pool allocators
- Pointer arithmetic — every rule, every trap
- Strings — `<string.h>` in full, safe vs unsafe functions, encoding
- The preprocessor — macros, token pasting, X-macros, include guards
- The C standard library in full — `<stdlib.h>`, `<math.h>`, `<time.h>`, `<locale.h>`, `<setjmp.h>`, `<signal.h>`, `<stdarg.h>`, `<complex.h>`, `<threads.h>`...
- Signal handling — `sigaction`, `sigprocmask`, async-signal safety rules
- Process management — `fork`, `exec`, `wait`, `waitpid`, `_exit`
- IPC — pipes, FIFOs, System V shared memory, POSIX shared memory, message queues, semaphores
- Threads — `pthreads`, mutexes, condition variables, rwlocks, barriers, TLS
- Networking — sockets, `bind`/`listen`/`accept`/`connect`, TCP/UDP in C
- The C memory model — `_Atomic`, `stdatomic.h`, memory orders
- Compiler internals — alignment, padding, calling conventions, ABI
- Inline assembly — `asm volatile`, constraint strings
- Build system — `make`, `cmake`, linking, static vs dynamic libraries
- Debugging — `gdb`, `valgrind`, `AddressSanitizer`, `UBSan`, core dumps
- C11 / C17 / C23 — new features, `_Generic`, `_Static_assert`, `_Noreturn`

---

So: the index is a complete map of **one branch** of one domain of C. We haven't even started on the language itself.

Want to keep going with file manipulation chapter by chapter, or do you want a master index of **all of C** first?
