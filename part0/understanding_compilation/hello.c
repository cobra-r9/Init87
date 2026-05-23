// this is the standard input output libraray header. This has all function declarations (the func signatures) and const vaules, macro definitions, etc. This is where we get the PUTS from .
#include <stdio.h>

// this is a macro : define will do this : define <word> <value>
// it is just a text substitution function in pre processor. 
// wherever it finds the word GREETING, it just replaces it with the value : "hello world!"
#define GREETING "hello, world!"

// the first function that ever runs: main, it returns an int type and takes zero arguments here.
int main(void) {
  // puts will print to the stdout.
  puts(GREETING);
  // finally we return the code 0 on success.
  return 0;
}

