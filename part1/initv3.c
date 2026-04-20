//=============================================================================
// file: initv3.c 
// date: 20-10-2026
// day: monday
// time: 08:54 
// description: experimentation for using printf without even importing stdio.h
// target: what would happen if we declare how printf is declared in our file itself instead of in stdio.h?
//=============================================================================



//#include <stdio.h>
// inspect the printf function whcih is declared int he stdio.h file. /usr/include/stdio.h
// here is the exact function declaration : extern int printf (const char *__restrict __format, ...);
// let's declare it then. 

extern int printf (const char *__restrict __format, ...);
// surprisingly, this works. why did it work? 
// using the extern function, we say the compiler to look for a function named printf in the glibc.so -> the standard libraray of c, with the following declarations, returns an integer, takes a char pointer, and a variable number of arguments. 
// i.e, the printf function is a variadic function, it can take variable number of arguments, with the first argument strictly being of type : const char *__restrict __format, ... means <anything else> and more importantly, the compiler does not know the type of arguments provided after the first argument.


int main(void) { 
    printf("Initialised first program!\n");
    
    return 0; 
}
