#include <stdio.h>
// include the standard input output header files.
#include <stdlib.h>
// include the c standard library header file.

// the main function, returns an integer value, takes void arguments : ie none.
int main(void) {
  srand(100);
  // initialise an integer r.
  int r;
  // do this after initilaising that integer.
  do {
    // assign r a rand value, modulo 100 to give some integer 
    r = rand() % 100;
    // print that integer
    printf("%d\n", r);
    // if the integer is not equal to 37, then do it again. if else, the do while loop ends. 
  } while (r != 37);
}

// note that the sequence of numbers are the same. we need to seed the random number using srand. What is srand?
// as the manpage tells, the rand function has a default seed as 1, and we can change the seed to some other integer. 
// case : the same srand always produces same sequence of numbers. you need to somehow dynamically change the seed in order to produce a different sequence of numbers. 
