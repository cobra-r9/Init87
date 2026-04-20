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


/*

This is the exact compiler error with the flags in makefile enabled.   


initv2.c: In function ‘main’: 
[decode] the error has occured in the main function.
initv2.c:15:5: error: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
   15 |     printf("Initialised first program!\n");
      |     ^~~~~~
[decode] at line 15, we have used printf function which is implicit, that is we did not define any function signature for the printf. 
initv2.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
  +++ |+#include <stdio.h>
    1 | //=============================================================================
[decode] compiler itself provides us the fix to include the stdio.h header file.
initv2.c:15:5: warning: incompatible implicit declaration of built-in function ‘printf’ [-Wbuiltin-declaration-mismatch]
   15 |     printf("Initialised first program!\n");
      |     ^~~~~~
initv2.c:15:5: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
[decode] OR PROVIDE A DECLARATION OF PRINTF -> this line is very clear. This error would not occur if we provide an explicit declaration for printf. 
I am gonna try that in v3. 
make: *** [Makefile:8: run] Error 1


*/ 
