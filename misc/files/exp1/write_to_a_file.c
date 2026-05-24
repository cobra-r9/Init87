// file : write_to_a_file.c 
// desc : the most basic write to file operation in C program using open and write, finally close it. 
// date : Sun, 24 May, 22:03
// We will be learning about the open file description, file descriptor and stuffs like that - the file related things. 
// open and write are unix syscalls. 
// we would need the following headers which will provide us what we need. 
// file control : fcntl.h : the file flags, O_WRONLY, mode_t for permissions, etc. 
// the unix sys calls - unix standard libraray : unistd.h for open write close calls. 
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

// a string for the path
const char* path = "./output/out1.txt";

// int for the flags, via the file open mode
// give it a open in write only mode, if the file does not exist, it need to create one, if the file already exists, in need to overwrite it or truncate the file. 
// these flags are ints on which we perform a bitwise or operation to get the value of specified set of properties in which the file is opened. 
// these flags are in the fcntl.h library 
// respectively, the flags are O_WRONLY for write only, O_CREAT for creating the file, O_TRUNC for truncate overwrite the file. 
int flags = O_WRONLY | O_CREAT | O_TRUNC;

// mode in which the file is opened and created : the permission bits. 
// this is the basic chmod bits for file permissions. read has a value 4, write has value 2 and execute has value 1. 
// we start this number with 0 so as to specify that it is to be represented in octal notation. 
// so, if we need to have read and write permission : it is 4 + 2 = 6, rxw? it is 4 + 2 + 1 =7, what about just read? it is 4. 
// owner group others : this is the order of the mode_t. 
// 0 6 6 4 - the owner can write, group can write, others can only read. 
mode_t mode = 0664;


// now that we need to define the main function 
int main(void) {
  // we would first use the open functon to open a file discriptor to the file:
  // the signature of the open function is as the follows : 
  // int open(const char*path, int flags, mode_t mode);
  // where const char* path is the path to the file we need to open relative to the running directory. 
  // now we need to open the file. open, if it fails, returns -1; we would have to check against it... 
  int fd = open(path, flags, mode);
  if (fd == -1) {
    // print to stderr, that the open failed. 
    perror("open failed!");
    // exit with return code 1. (non zero return code means error.)
    return 1;
  }

  // buff is a char array. the buffer we need to write.
  char buff[] = "hello world! this is a modifyable buffer.\n";
  // note : at the end of the buff is the \0 : null terminator, which we actually don't want. 

  // now we need to write to the file. 
  // we use the write function which has the following signature. 
  // it returns a ssize_t type .What is that ssize_t? we know what size_t is, ssize_t is signed size_t, where basic size_t is unsigned. 
  // ssize_t write(int fd, void *buff, size_t buff_size);
  // on success it returns buff_size, where it is the buffer size, the amount of data writeen. on failure, it returns less than buff_size, partialy write, or something that is not equal to buff_size. 
  // we would have to check for any failures. 
  // this is because we are not required to use any cast explictly like in c++, I did this so to intentionally be explicit that this is the type of that param. 
  // not considering the finall byte : \0 null terminator : that's where there is that -1
  if (write(fd, (void *)buff, sizeof(buff) - 1) != sizeof(buff) - 1) {
    // print to standard error that write failed. 
    perror("write failed!");
    // but we shall never forget to close the file. 
    // the close will return -1 on error, we need to check against it for errors.
    if (close(fd) == -1) {
      // print to standard error the failed to close fd.
      perror("failed to close fd");
      // return a non zero return code. 
      return 1;
    }
    // return a non zero return code. 
    return 1;
  }

  // the final close if write succeeds. The same reason as prescribed. 
  if (close(fd) == -1) {
    perror("failed to close fd");
    return 1;
  }

  // finally return 0 on success.
  // note that the output directory should exist
  return 0;
}
