// name : multi-declaration.c 
// date : 2026-06-28 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

// multi-declaration
void function(void);
void function(void);

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Multiple declarations.");
    function();
    return EXIT_SUCCESS;
}

// single definition
void function(void) {
    puts("success");
}

