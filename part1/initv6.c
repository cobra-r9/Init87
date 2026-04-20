//=============================================================================
// file: initv6.c
// date: 20-04-2026
// day: monday
// time: 09:43
// description: demonstration of function shadowing; recreating formatless printf, after correcting the error.
// target: without importing the stdio.h, define a custom printf function, pass to puts.
//=============================================================================



// #include <stdio.h> not included...
// stealing the puts function signature from the stdio.h : extern it. 

extern int puts (const char *__s);

// declaration of the printf definition. Note, we are not externing it, just declaring it.
int printf(const char *__restrict __format, ...);
// we are telling the compiler in advance that : hey, this is how the printf's signature looks like, so that we can use it actually before even defining, ie, but we have to define it later for sure.


int main(void) {
    printf("Hello World!, This is usefull this time, and not errored.\n"); 
}


int printf(const char *__restrict __format, ...) {
    puts(__format); 
    return 0;
}


