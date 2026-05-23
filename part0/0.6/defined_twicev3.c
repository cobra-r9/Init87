// No stdio.h — we declare everything ourselves.

// FILE is a struct defined by the C runtime. We forward-declare it as an
// opaque struct — we don't need to know its internals, just that it exists.
#include <stddef.h>

typedef struct _IO_FILE FILE;

// Now we declare the signatures of every standard function we use.
extern FILE *fopen (const char *__restrict __filename,
		    const char *__restrict __modes);
extern int fclose (FILE *__stream);
extern void  perror(const char* s);
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
		      size_t __n, FILE *__restrict __s);

// Our own modified puts — no conflict now because stdio.h is gone.
int puts(const char* __s, int buff_size) {
  FILE* file = fopen("output.txt", "w");
  if(file == nullptr) {
    perror("Failed to open file");
    return 1;
  }
  if (fwrite((void *)__s, 1 * buff_size, 1, file) != 1) {
    perror("Failed to write");
    fclose(file);
    return 1;
  }
  fclose(file);
  return 0;
}

int main(void) {
  puts("HELLO : is this in a file?", 5);
  return 0;
}
