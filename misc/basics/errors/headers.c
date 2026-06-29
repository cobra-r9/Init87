// name : headers.c 
// date : 2026-06-29 
// std  : C 23 standard 


// how to compile this : gcc headers.c anotherconstant.c -o main 

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include "constant.h"

const char* constant = "help";
const char* realconstant = "hello?";

//--------------------------------------- main program ----------------------------------
int main(void) {
    

    // with 'constant' being available in both the headers. 
    printf("This was redefined in another file: %s\n", constant);
    printf("This was from anotherconstant.c: %s\n", anotherconstant);
    printf("This was from constant.c: %s\n", realconstant);    
    return EXIT_SUCCESS;
}

// you will get an error from the linker. stating the following. 

/*
gcc headers.c anotherconstant.c -o main
/usr/bin/ld: /tmp/ccf5HVKo.o:(.data.rel.local+0x8): multiple definition of `constant'; /tmp/ccZYdZ35.o:(.data.rel.local+0x0): first defined here
collect2: error: ld returned 1 exit status
 */
