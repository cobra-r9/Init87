//=============================================================================
// file: initv2.c 
// date: 19-10-2026
// day: sunday
// time: 10:47 
// description: A hello world code without importing stdio.h
// target: What will happen, in case you forgot to include stdio.h, or any other header file?
//=============================================================================


// #include <stdio.h>
// include is commented out for testing purposes. See what happens to the gcc compiler without the include.

int main(void) { 
    printf("Initialised first program!\n");
    // note that we are calling a printf function about which the compiler has no idea about where it exists, function signature, etc, all which will be determinted by compiler from stdio.h. But recent years, the dumb C compiler has become smart enough to catch this as error.
    // respect the C compiler because it respects you.
    return 0; 
} 
