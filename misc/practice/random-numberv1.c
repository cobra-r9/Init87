#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int r;
  do {
    r = rand() % 100;
    printf("%d\n", r);
  } while (r != 37);
}
