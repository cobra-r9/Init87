//=============================================================================
// file: initv5.c
// date: 20-04-2026
// day: monday
// time: 09:34
// description: demonstration of function shadowing; recreating formatless printf
// target: without importing the stdio.h, define a custom printf function, pass to puts.
//=============================================================================



// #include <stdio.h> not included...
// stealing the puts function signature from the stdio.h : extern it. 

extern int puts (const char *__s);

// declaration of the printf definition. Note, we are not externing it, just declaring it.
int printf(const char *__restrict __format, ...);
// we are telling the compiler in advance that : hey, this is how the printf's signature looks like, so that we can use it actually before even defining, ie, but we have to define it later for sure.


int main(void) {
    printf("Hello World!, This is usefull this time."); 
}


int printf(const char *__restrict __format, ...) {
    puts(__restrict __format); // what? __restrict is a keyword: I realised that after highlight blue? probably this is not gonna work. 
    return 0;
}

// but I do not know why : see v6, *__restrict __format cannot be passed? 
// dangling question: what exactly is extern(partially aware), __restrict (completely unaware). I have learnt and wrote what this is in the section given below. But also in the Init87 error blog; md files stuff. 


// compiler error : 

/*

initv5.c: In function ‘printf’:
initv5.c:28:10: error: expected expression before ‘__restrict’ 
[decode] __restrict has something to do with expressions.
   28 |     puts(__restrict __format); // what? __restrict is a keyword: I realised that after highlight blue? probably this is not gonna work.
      |          ^~~~~~~~~~
initv5.c:27:35: warning: unused parameter ‘__format’ [-Wunused-parameter]
   27 | int printf(const char *__restrict __format, ...) {
[decode] alright then, it is not __restrict __format, but just __format which is the parameter I have to actually pass. Wonderful. It is also quite noticable in the stdio.h that the function parameters are in the form __<variable name>; signature visible even in the extern of puts. 
      |            ~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~
make: *** [Makefile:8: run] Error 1

*/
// next? do it correct : __format, and it should run in my opinion. 
