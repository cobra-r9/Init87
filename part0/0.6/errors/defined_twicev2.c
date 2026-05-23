// now that we can declare the signature of the functoin multiple times. What about definition of the function?
// we use another puts to print a value.

// #include <stdio.h>  this is fix for v1 file. this is v2.


extern int puts(const char* __s, int buff_size);
// modify the puts function to write to a file instead of output to stdout.
int puts(const char* __s, int buff_size) {
  // open a file pointer. use fopen to open a file output.txt in write mode.
  FILE* file = fopen("output.txt", "w");
  // if the file fopen failed, then it returns a null pointer instead of file pointer. 
  // standard safety checks check if the file is nullptr, then it implies fopen failed.
  if(file == nullptr) {
    // flush to error, print error : failed to open file.
    perror("Failed to open file");
    // return a non zero exit code. 
    return 1;
  }

  // again, fwrite is another function : syntax : fwrite(void *ptr : points to what data to write, size of data : size_t datasize, number of items to write : size_t count, FILE* stream : the filestream to write to); 
  // it returns the number of items returned, ie, the count. If it returns count, then it succeeded, else it failed. We check against it here. 
  if (fwrite((void *)__s, buff_size, 1, file) != 1) {
    // flush to the error, print the error failed to write.
    perror("Failed to write");
    // never forget to close the opened file. 
    fclose(file);
    // finally exit with non zero return code. 
    return 1;
  }

  // close the file.
  fclose(file);
  // return 0 on success.
  return 0;
}

// now comes our main function. 
int main(void) {
  puts("HELLO : is this in a file? If so, it succeeded. Else, try to remove the header and try again.", 5);
  // write first 5 bytes alone : only HELLO should be found in the file
  return 0;
}

/*
 *

 gcc defined_twice.c -o defined_twice
defined_twice.c:7:12: warning: conflicting types for built-in function ‘puts’; expected ‘int(const char *)’ [-Wbuiltin-declaration-mismatch]
    7 | extern int puts(const char* __s, int buff_size);
      |            ^~~~
defined_twice.c:1:1: note: ‘puts’ is declared in header ‘<stdio.h>’
  +++ |+#include <stdio.h>
    1 | // now that we can declare the signature of the functoin multiple times. What about definition of the function?
defined_twice.c: In function ‘puts’:
defined_twice.c:11:3: error: unknown type name ‘FILE’
   11 |   FILE* file = fopen("output.txt", "w");
      |   ^~~~
defined_twice.c:11:3: note: ‘FILE’ is defined in header ‘<stdio.h>’; this is probably fixable by adding ‘#include <stdio.h>’
defined_twice.c:11:16: error: implicit declaration of function ‘fopen’ [-Wimplicit-function-declaration]
   11 |   FILE* file = fopen("output.txt", "w");
      |                ^~~~~
defined_twice.c:11:16: note: ‘fopen’ is defined in header ‘<stdio.h>’; this is probably fixable by adding ‘#include <stdio.h>’
defined_twice.c:11:16: error: initialization of ‘int *’ from ‘int’ makes pointer from integer without a cast [-Wint-conversion]
defined_twice.c:16:5: error: implicit declaration of function ‘perror’ [-Wimplicit-function-declaration]
   16 |     perror("Failed to open file");
      |     ^~~~~~
defined_twice.c:23:7: error: implicit declaration of function ‘fwrite’ [-Wimplicit-function-declaration]
   23 |   if (fwrite((void *)__s, buff_size, 1, file) != 1) {
      |       ^~~~~~
defined_twice.c:23:7: note: include ‘<stdio.h>’ or provide a declaration of ‘fwrite’
defined_twice.c:23:7: warning: incompatible implicit declaration of built-in function ‘fwrite’ [-Wbuiltin-declaration-mismatch]
defined_twice.c:23:7: note: include ‘<stdio.h>’ or provide a declaration of ‘fwrite’
defined_twice.c:27:5: error: implicit declaration of function ‘fclose’ [-Wimplicit-function-declaration]
   27 |     fclose(file);
      |     ^~~~~~

 *
 */

// inference : ah, how bad is it? If I fail to include the header, the file stuffs will be gone. So the original fix is, remove header + use extern to provide declarations.
