#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <stddef.h>


int file_write_wct(const char *path, const void *data, ssize_t buff_size, mode_t mode) {

  // open() returns a file descriptor : a small integer that indexes into this process's fd table in the kernel.
  // The fd is our handle to the open file description, which tracks offset, flags, and points to the inode. Say, fd is the roll number of several files in the open file description, and you call that open file description(a kernel level object) which has a pointer to inode of that file. You access that particular file using it's roll number (fd); it's properties - say the way in which it is opened (as given below, the (O_WRONLY) mode), etc stuffs are stored in a object called the open file discription along with the offset of bytes from where it need to start read or write. (in this case write.)
  int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);

  // open() returns -1 specifically on failure (not just any negative number : so remember to safe check if oopen returned a file discroptor).
  if (fd == -1) {
    return 1;
    // as far as our plan for this command is concerned, we need to return 1 in case open command failed.
  }

  // here is what exactly this write command does. 
  // inside an if block, if there is a function, first the function is evaluated, then the comparision is done, and the if is executed based on the logic it determines to undergo
  // write(int fd, const void *buf, size_t count) -> ssize_t
  // Copies exactly 'buff_size' bytes from 'data' into the file.
  // write() is completely type-blind — it writes raw memory bytes as-is.
  // No null terminator logic : that headache comes only when you deal with the fprintf and files, fputs, etc, fopen, which we will deal later after MASTERING the fd stuffs and flags. Write multiple lines? use a newline stuff in case of ascii text. Or need a binary blob to be written? use #embed feature of the C23 to embed exactly same bin blob.
  // this write returns the number of bytes actually written.
  // Partial writes are possible (signals, pipes, etc.) — always check.
  if (write(fd, data, buff_size) != buff_size) {
    close(fd);  // never leave an fd open on failure.
    return 2; // similarly, as far as our functoin is concerned.
  }

  close(fd); // never forget to close the fd. but what happens if you close the fd two time? let's check it later (find it in the errors directory.)
  return 0; // return 0 on success.
}

char data[] = {
#embed "hello"
};
int main(void) {
  file_write_wct("output", data, sizeof(data), 0777);
}
