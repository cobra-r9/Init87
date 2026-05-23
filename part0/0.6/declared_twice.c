// what happens if we do a function declaration twice?
// we will include the stdio.h header which already defined the signature of puts. 
// now we then use extern to declare the puts again.

#include <stdio.h> 

extern int puts(const char* __s);
int main(void) {
  puts("hello world!");
}
