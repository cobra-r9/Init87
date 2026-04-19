//=============================================================================
// file: initv1.c 
// date: 19-10-2026
// day: sunday
// time: 10:20 
// description: This is the first program in the Init87 project for learning C. Basically - hello world.
//=============================================================================


// this is a comment in c.
// this is not my first c code either
// for traditional reasons anyway
// use : c pre proecessor to include standard input and out put library
// include <...> searchs the system wide include paths.
// include "..." first searches the current directory - falls back to the systemwide path 
// anything which starts with a # is not a C command, but a cpp : c pre processor operation

#include <stdio.h>
// include the c standard input output library header file which has stuffs like printf, scanf, etc....

// the first function which executes after binary execution is main. Main, but default, SHOULD be set to return integer.
int main(void) { // with this {, we declare start of a scope, a code block.
    // printf function will print it's first argument to the stdout, other arguments provided are parsed into the first argument via a formatter stuff.
    printf("Initialised first program!\n");
    // but printf is a overhead here. As we are not gonna do any of formatting stuffs, why use a function with a formatter functionality? putchar : this puts a single character to the stdout. (standard output). puts : this puts a line, as string, or whatever raw is passed into it's first argument and ACCEPTS NO OTHER ARGUMENTS. printf is a variadic function : meaning, you can pass a variable number of arguments as per the requirements for formatting strings, floats, integers, characters, long forms, size_t, etc types. But as we are only printing a hello line with zero formatting requirements, in an optimisation allowed compiler, the compiler will automatically optimise the code, replacing the printf call with puts. 
    // return's zero when success. Any non zero return implies failure point.
    return 0; 
} // with }, we define the end of a code block, a scope. In this case, it is main scope ends here.
