// now that we can declare the signature of the functoin multiple times. What about definition of the function?
// we use another puts to print a value.

#include <stdio.h> 


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


/* errors
 *
 

defined_twice.c:7:12: error: conflicting types for ‘puts’; have ‘int(const char *, int)’
    7 | extern int puts(const char* __s, int buff_size);
      |            ^~~~
In file included from defined_twice.c:4:
/usr/include/stdio.h:718:12: note: previous declaration of ‘puts’ with type ‘int(const char *)’
  718 | extern int puts (const char *__s);
      |            ^~~~
defined_twice.c:9:5: error: conflicting types for ‘puts’; have ‘int(const char *, int)’
    9 | int puts(const char* __s, int buff_size) {
      |     ^~~~
/usr/include/stdio.h:718:12: note: previous declaration of ‘puts’ with type ‘int(const char *)’
  718 | extern int puts (const char *__s);
      |            ^~~~ 


 *
 */


// Doubt : I know that this is the fix : remove the header file, (comment it), but why does it fail this way?
