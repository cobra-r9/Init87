// now that we can declare the signature of the function multiple times. What about definition of the function?
// we use our own puts to redirect stdout to a file instead.

#include <stdio.h>

// we declare the signature first using extern. since stdio.h already declared puts with the same signature,
// this is a legal re-declaration — two identical promises to the compiler cause no conflict.
extern int puts(const char* __s);

// modify the puts function to write to a file instead of output to stdout.
// by defining puts ourselves, the linker will prefer our definition over the one in libc.
// this works because the linker resolves our object file before reaching into the standard library.
int puts(const char* __s) {

  // open a file pointer. use fopen to open output.txt in write mode.
  // "w" means : create the file if it doesn't exist, truncate it to zero if it does.
  FILE* file = fopen("output.txt", "w");

  // if fopen failed, it returns a null pointer instead of a valid file pointer.
  // nullptr is the idiomatic null pointer constant in C23, unambiguously a pointer — not an integer zero.
  // standard safety check : if file is nullptr, fopen failed and we should not proceed.
  if(file == nullptr) {
    // perror flushes to stderr and prints the OS-level reason for the failure.
    perror("Failed to open file");
    // return non-zero to signal failure to the caller.
    return 1;
  }

  // fputs writes a null-terminated string to a file stream.
  // syntax : fputs(const char* s, FILE* stream)
  // on success it returns a non-negative integer (exact value unspecified by the standard).
  // on failure it returns EOF, which is a macro defined as -1 in stdio.h.
  // we check against EOF to detect write failure.
  if (fputs(__s, file) == EOF) {
    // flush the OS-level error reason to stderr.
    perror("Failed to write");
    // never forget to close an opened file — even on the failure path.
    // forgetting fclose here would leak the file descriptor.
    fclose(file);
    // return non-zero to signal failure.
    return 1;
  }

  // close the file. fclose flushes the internal buffer to disk and releases the resource.
  // skipping fclose is a real bug — data sitting in the buffer may never reach the file.
  fclose(file);

  // return 0 to signal success.
  return 0;
}

// now comes our main function.
int main(void) {
  // calls our puts, not libc's — the linker already chose our definition.
  // the entire string goes to output.txt instead of stdout.
  puts("HELLO : is this in a file? If so, it succeeded. Else, try to remove the header and try again.");
  return 0;
}
