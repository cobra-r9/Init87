// name : multi-definition.c 
// date : 2026-06-28 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

// se what happens if multiple defintion of the same struct is provided.
// here note that we are using the typedef. Which implies that - there can be just one type. 
typedef struct {
    int a;
    char i[4];
    double b;
} mystruct_t;

// comes the second definition
// here again we are doing another typedef. There is a conflict. It gives a redefinition error. 
typedef struct {
    int a;
    char i[4];
    double b;
} mystruct_t;

// note that we account for the null terminator too. 
mystruct_t MyStruct = {4, "why", 234.23};

//--------------------------------------- main program ----------------------------------
int main(void) {
    

    puts("Multi defintion");
    printf("String : %s\n", MyStruct.i);
    return EXIT_SUCCESS;
}

// here is the error : 

/*
 
multi-definition.c:24:3: error: conflicting types for ‘mystruct_t’; have ‘struct <anonymous>’
   24 | } mystruct_t;
      |   ^~~~~~~~~~
multi-definition.c:16:3: note: previous declaration of ‘mystruct_t’ with type ‘mystruct_t’
   16 | } mystruct_t;
      |   ^~~~~~~~~~
make: *** [/home/cobra/.Makefile-default:8: run] Error 1

 */

// note that - the previous declaration. Huh. 
// The fix is simple - you remove one definitoin. But there is another case, if you remove the typedef, it is literally - yes techincally valid code. see the v2 code. 
