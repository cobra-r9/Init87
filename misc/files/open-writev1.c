// Unix File I/O — opening, writing, and understanding raw binary vs text.
// Uses POSIX syscalls exposed via unistd.h and fcntl.h.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


// A simple 3D coordinate struct stored as raw floats.
typedef struct {
  float x, y, z;
} Coordinates;


// file_write_wct : write + create + truncate.
// Opens a file at 'path' in write mode.
// Creates the file if it does not exist.
// Truncates (overwrites) the file if it already exists.
//
// Flags used (defined in fcntl.h):
//   O_WRONLY : open for writing only
//   O_CREAT  : create the file if it does not exist
//   O_TRUNC  : truncate the file to zero length if it already exists
//              (capital O, not zero!)
//
// 'mode' sets the file permissions on creation (mode_t — same permission
// bits as chmod). Ignored if the file already exists.
//
// Returns:
//   0  on success
//   1  if open() failed      (fd == -1)
//   2  if write() failed or wrote fewer bytes than expected
//
int file_write_wct(const char *path, const void *data, ssize_t buff_size, mode_t mode) {

  // open() returns a file descriptor : a small integer that indexes into
  // this process's fd table in the kernel. The fd is our handle to the
  // open file description, which tracks offset, flags, and points to the inode.
  int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);

  // open() returns -1 specifically on failure (not just any negative number).
  if (fd == -1) {
    return 1;
  }

  // write(int fd, const void *buf, size_t count) -> ssize_t
  // Copies exactly 'buff_size' bytes from 'data' into the file.
  // write() is completely type-blind — it writes raw memory bytes as-is.
  // No null terminator logic, no string semantics. Pure bytes.
  //
  // Returns the number of bytes actually written.
  // Partial writes are possible (signals, pipes, etc.) — always check.
  if (write(fd, data, buff_size) != buff_size) {
    close(fd);  // never leave an fd open on failure.
    return 2;
  }

  close(fd);
  return 0;
}


int main(void) {
  puts("INITIALISED...");

  // --- Writing a plain string ---
  // Each byte is in the ASCII printable range (32-126).
  // The 'file' command will identify this as "ASCII text".
  int ret = file_write_wct("output.txt", "hello world!\n", 13, 0664);

  // --- Writing a raw struct ---
  Coordinates coor = { 8.4f, 12.7f, 19.2f };
  ssize_t size_coor = (ssize_t)sizeof(coor);

  printf("x : %f\ny : %f\nz : %f\n", coor.x, coor.y, coor.z);

  // We cast to void* because file_write_wct takes raw memory.
  // The struct is written as 12 bytes of IEEE 754 binary float data.
  // The 'file' command will call this "data" — not text — because the
  // bytes fall outside the printable ASCII range. The .txt extension
  // means nothing to Unix; the kernel and tools like 'file' look at
  // the actual byte content, not the filename.
  ret = file_write_wct("new_out.txt", (const void *)&coor, size_coor, 0664);

  // Permission breakdown for 0664:
  //   0    : leading zero = octal literal (permissions are always octal)
  //   6    : owner  — read(4) + write(2) = 6
  //   6    : group  — read(4) + write(2) = 6
  //   4    : others — read(4) only

  // Use fprintf to stderr for custom error codes.
  // perror() prints the system errno message, which may be stale
  // by the time we reach here (close() inside the function can overwrite it).
  if (ret == 1) {
    fprintf(stderr, "error: failed to open file\n");
    return 1;
  }
  if (ret == 2) {
    fprintf(stderr, "error: write failed or partial write\n");
    return 1;
  }

  return 0;
}

// but doubts! doubts : 
// why did the file <filepath> command's output to file output.txt an ASCII text, but not the file new_out.txt a data type? Though both have a .txt file type? 
//----- See that : output ----- 
/* 
 *
This is the output of the file : 
new_out.txt: data
doubts will be clarified on the Init87 doubts session. 
 *
 */
