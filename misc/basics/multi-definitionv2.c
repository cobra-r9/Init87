// name : multi-definitionv2.c 
// date : 2026-06-28 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

// se what happens if multiple defintion of the same struct is provided.
struct mystruct{
    int a;
    char i[4];
    double b;
};

// comes the second definition
struct mystruct{
    int a;
    char i[4];
    double b;
};

// note that we account for the null terminator too. 
struct mystruct MyStruct = {4, "why", 234.23};

//--------------------------------------- main program ----------------------------------
int main(void) {
    

    puts("Multi defintion");
    printf("String : %s\n", MyStruct.i);
    return EXIT_SUCCESS;
}


