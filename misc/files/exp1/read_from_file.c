#include <stdio.h> 
// for perror 
#include <fcntl.h> 
// for file flags : O_WRONLY, O_RDONLY, etc flags. 
#include <unistd.h> 
// for open, read, close function calls of unix. 


int main(void) {
  // initialise an empty buffer of 256 size. 
  int buff_size = 256;
  char buff[buff_size];
  // initialise a byte tracker so that we can track the number of bytes read with it. 
  int bytes_read;

  // now that we need to use the fd to connect to the open file description. 
  // we shall use the open function for this, read from the ./output/out1.txt file. 
  // here, we are not gonna write anything. therefore, the open function does not require any permission flags to be set. 
  // in normal case : int open(const char *path, int flags, mode_t mode);
  // in case we are gonna write, we create a new file for the first time, we use the 0_CREAT flag to create it if it does not exist. During the file creation, the permission bits have to be encoded in the inode, where the inode has all the metadata, and a pointer to original data in the disk 
  // but we are just gonna read from the file. we use O_RDONLY flag to read, that's it. nothing else. so the mode_t argument shall not be provided. 
  // BUT : beware. when you are writing, if you are not providing the mode_t argument, you would be allowing the compiler to read from garbage and arbitary permission bits would be set. 
  int fd = open("./output/out1.txt", O_RDONLY);
  // check if it failed. on failure, the open returns -1. then perror it, so that the output is appended along with the actual error. 
  if (fd == -1) {
    perror("open failed!");
    // exit with a return code 1. 
    return 1;
  }

  // now that we need to read. but what if the data we need to read is greater than the buffer size we allocated? here is why we need to track the bytes_read. we would be performing a while loop. 
  // read till buff_size - 1 bytes : because we deliberately need the last byte appended with a null terminator. We need that null terminator because we use printf to print it. The stream terminates only on encountering the \0 null terminator. so logically we need to assign the final byte with a '\0' character. The same goes for stdout. but here we would not be using the printf to print to the stdout. we will be writing to stdout : fd : 1, stdin is fd 0; stderr is fd 2. we use write to write to the stdout.  

  // the signature of read is int read(int fd, void *buff, size_t buff_size); 
  // it returns the number of bytes read. if it read bytes, it returns the number of bytes read. if it has nothing else to read, it returns 0, else, on error -1; 
  // NOTE : previously, I left a little of error; 
  // while just evaluates the assignment. so if we need to evaluate a statement + assign it to some variable, we need to enclose the assignment statement into a seperate parentheses. like (assigned = some_funct(p1, p2, p3)) > comparision;
  // not doing so will lead to improper assignment and you would not get the output what you expected. 
  while ((bytes_read = read(fd, buff, buff_size - 1)) > 0) {
    /* check if read failed and exit accordingly after closing the file. 
    if (bytes_read == -1 || bytes_read < 0) {
      perror("read failed, closed fd.");
      close(fd);
    }
    */
    // but wait. that above block is redundant. our while loop runs only if the bytes_read is > 0; but why are we doing the comparision for it being less than zero? real bug. 
    // so I am gonna comment this out and move it out of the while loop.

    // if it did not fail, append the last byte as a null terminator and print the buffer 
    buff[bytes_read] = '\0';
    // ah, what is that? STDOUT_FILENO? it is fd number of standard output : 1; we are just doing what puts does, but in a different format!. 
    // these values are from fcntl.h;
    if (write(STDOUT_FILENO, buff, bytes_read) != bytes_read) {
      perror("write to stdout failed!");
      return 1;
    }
  }
  if (bytes_read == -1) {
    perror("read failed, closed fd.");
    close(fd);
    return 1;
  }

  // finally close the fd after read completes. 
  if (close(fd) == -1) {
    perror("close failed!");
    return 1; 
  }
  // on success, return code 0;
  return 0;
}
