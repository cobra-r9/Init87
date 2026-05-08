#include <stdio.h>
//#include<stdio.h> is also a valid point in C. it does not care about the space stuffs.

int main(void)
// completely valid
{
  printf("hello, world!\n") // not valid : missing ;
  return 0;
}
