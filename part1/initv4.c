//=============================================================================
// file: initv4.c
// date: 20-04-2026
// day: monday
// time: 09:14
// description: demonstration of function shadowing.
// target: without importing the stdio.h, define a custom printf function, doing nothing.
//=============================================================================



//#include <stdio.h> not included...

// declaration of the printf definition. Note, we are not externing it, just declaring it.
int printf(const char *__restrict __format, ...);
// we are telling the compiler in advance that : hey, this is how the printf's signature looks like, so that we can use it actually before even defining, ie, but we have to define it later for sure.


int main(void) {
    printf("Hello World!, This is useless"); 
    // we are using the printf function we defined.
}

// printf function which takes arguments, as exact of original printf, but it just returns 0; 
// what we have done below is known as defining a function. 
int printf(const char *__restrict __format, ...) { // with the -Wextra flag enabled, the compiler will warn us about unused __format, because we are not using any formating stuff. We can learn about each and every signature of the function later, in the pathway when specifically learning about the stdio.h, for now, it is good enough to know that compiler warns with the flang -Wextra enabled. 


    // so it is possible for me to steal the function signature of puts and make printf do what exactly puts does? let's see.
    return 0;
}


