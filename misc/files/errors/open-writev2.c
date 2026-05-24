// Unix File I/O — opening, writing, and understanding raw binary vs text.
// Uses POSIX syscalls exposed via unistd.h and fcntl.h.
// file : open-writev2.c 
// purpose of existence : what happens if we do a close on a file discriptor two times? 
// let's use this file for that purpose. But this time, additionally, instead of a struct, we are going to use legendary C23's embed macro for the first time to embed the C binary of open-writev1.c as in array : we call that as a what? say v1dup? 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
// A simple 3D coordinate struct stored as raw floats.
// this thing is an anoymous struct, which is later typedefed to a type Coordinates. 
typedef struct {
  float x, y, z;
} Coordinates;

// embeds can be only determined in global scope, not inside any function. so we need to use it here, if not no where. create a const char array (not char pointer) of data : 
const char data[] = {
#embed "../v1dup"
};

// that's all, the embedding is over. 
// file_write_wct : write + create + truncate.; this is what I named this function, the wct stands for what it actually is. 
// it opens a file at 'path' in write mode, then...
// it creates the file if it does not exist. (that create flag)...
// it truncates (overwrites) the file if it already exists, that is in sense, overwriting. 
// Flags used (these flags are very well defined in fcntl.h : spell it as file control.):
//   O_WRONLY : open for writing only (as the name indicates)
//   O_CREAT  : create the file if it does not exist (similarly, as the name indicates)
//   O_TRUNC  : truncate the file to zero length if it already exists. (but here it does not have O_OVERWRITE stuff, it is truncate.)
//   (capital O, not zero! - I missed it previously, then ran into a gcc error, then have this comment - never forget Os...)



// 'mode' sets the file permissions on creation (mode_t — same permission
// bits as chmod). This setting of mode step is ignored if the file already exists.

// this function I wrote - ...wct stuff returns:
//   0  on success - so you can verify (for most safest possible code, verify all return values, but I did not do that all-verify here.)
//   1  if open() failed      (fd == -1) (verify - see what failed.)
//   2  if write() failed or wrote fewer bytes than expected. (finally, this verification in the main, check the returns.); 
//   Moreover, I guess, we can spin up an enum type : say wct_error enum, have these flags labeled and use a switch statement to do a stderr : fprintf output.
// here comes out function definition. 
// get a const char* path : constant char pointer, a string which is opened as a file in the pwd.
// a const void *data : const is important here because we are not going to MUTATE the data using some chemical warfare agents or some biological lore stuff. That is : you just need to write the data after reading the data to some other location. That's it. This data may be of any type, that is why we use a void* type. (un)fortunately, we cannot derefernce the void pointer.
// ssize_t : what ? is that a typo? only size_t is what I have used previously? Nah!!.
// size_t stands for size type. (in physics stuffs like that, we consider sizes as non negative values, so size naturally is a size, non negative.)
// but if you do not care about the size being negative or non negative as in case of this quadratic equation, where x is the dimenstion of the square, x**2 + 1 = 0, but yeah, there exists such a square in the complex plane lol. 
// ssize_t exists similarly for wierd enough reason - write command returns ssize_t, and that ssize_t is negative if it is errored (though only in some case).
// finally we have the mode_t type, which is nothing but integer like notation for specifiying what we use in the chmod command to set permission flags. 
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
  // here comes the second close : 
  close(fd);
  return 0; // return 0 on success.
}

// exhausted? But see, the main picture has not arived yet.


int main(void) {
  puts("INITIALISED..."); // just for fun puts.

  // --- Writing a plain string ---
  // Each byte is in the ASCII printable range (32-126). (that is why it is ascii!)
  // The 'file' command will identify this as "ASCII text".
  // tell compiler to allocate the memory without specifiying bytes. 
  //int ret1 = file_write_wct("output.txt", msg, sizeof(msg), 0664); sizeof(msg) : you need to remember the concept of the array decomposiition. when passed as arguments, the array decomposes to pointer. in x86 it is 8 bytes, so only 8 characters : #include are written. So use strlen instead. 
  // int ret1 = file_write_wct("output.txt", msg, strlen(msg), 0664);
  // we have been complicating this command. strlen of message? hell nah. why should we use strlen? it was because we had type of msg as const char*, which in sense means it is a opinter (char pointer.); sizeof(..) perfectly work on arrays; const char data[]; done. 
  int ret1 = file_write_wct("duplicate.elf", data, sizeof(data), 0774);

  if (ret1 == 1) {
    fprintf(stderr, "error: failed to open file for dupv1 writing\n");
    return 1;
  }
  if (ret1 == 2) {
    fprintf(stderr, "error: write failed or partial write for dupv1 writing\n");
    return 1;
  }


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
  int ret2 = file_write_wct("new_out.txt", (const void *)&coor, size_coor, 0664);

  // Permission breakdown for 0664:
  //   0    : leading zero = octal literal (permissions are always octal)
  //   6    : owner  — read(4) + write(2) = 6
  //   6    : group  — read(4) + write(2) = 6
  //   4    : others — read(4) only

  // Use fprintf to stderr for custom error codes.
  // perror() prints the system errno message, which may be stale
  // by the time we reach here (close() inside the function can overwrite it).
  if (ret2 == 1) {
    fprintf(stderr, "error: failed to open file for coor writing\n");
    return 1;
  }
  if (ret2 == 2) {
    fprintf(stderr, "error: write failed or partial write for coor writing\n");
    return 1;
  }

  return 0;
}

// this is the error section and doubt section: 
//----- See that : output ----- 
/* 
 

though having two close() operating on same fd, I did not get any error. why? 
compiler version 16.1.1, supports embed officially, gcc 
standard used c23 
why? did not it error? 

cd ../ and see the open-writev1 file. 
that file outputs the following in the output.txt 

#include <stdio.h>
int main(void) {
	//this is a comment in C
	puts("hello world!");
}

Now we have that open-writev1's program binary, called ../v1dup 
this v1dup, on executed, writes the above hello world code to output.txt. 
we have embedded the v1dup code in data array and instructed the compiler to write that as 774 (rxw, rxw, r) : as duplicate.elf. 

Everything is ok, and the duplicate.elf is generated and when you execute it, it goes fine, producing output.txt and the hello world code in it. the new_out.txt is produced by v1 dup. But out program binary has already generated a new_out.txt, which would be overwritten by the duplicate.elf? 


the output of our file : when duplicate.elf in file_write_wct is renamed to output.txt is this : 

INITIALISED...
x : 8.400000
y : 12.700000
z : 19.200001

Here it comes interesting. duplicate.elf comes interesting. You rename in our this file, v2 file, duplicate.elf to output.txt, you get the binary v1dup masked as the output.txt. But when you execute that output.txt file, you get this following error. 

INITIALISED...
error: failed to open file for str writing 


In case you have it same as the duplicate.elf 

Our v2 program generates new_out.txt and duplicate.elf
INITIALISED...
x : 8.400000
y : 12.700000
z : 19.200001

and when you execute the duplicate.elf, it produces output.txt and overwrites the new_out.txt 

INITIALISED...
x : 8.400000
y : 12.700000
z : 19.200001

Why does it happen?????


 *
 */
