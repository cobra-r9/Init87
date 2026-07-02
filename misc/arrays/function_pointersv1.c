// name : function_pointers.c 
// date : 2026-07-01 
// std  : C 23 standard 






//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

// this following code describes the usage of the function pointers and their significance in dispatch tables. 
// suppose : we define a function called foo, which is a pointer to an array of 10 pointers to a function which returns a type char* by taking an int. 

char* (*(*foo)[10])(int) = NULL;


// there exists a function called set_dspatch, which will take the pointer to an array of 10 pointers to a function which will take int, returning a char*, and then sets the value of foo to that pointer. 
void set_dispatch(char* (*(*table)[10])(int)) {
    foo = table; 
    return;
}

// these are the handlers, which will return various status code based on the integer is even or odd. 
// this will return the error or ok string. 
char* handle(int code) {
    if (code % 2 == 0) {
       return "OK";
    } else {
        return "ERROR";
    }
}

// then we create an array of function pointers array: normal table is array of 10 pointers to a functoin which takes int and returns string. 
char* (*normal_table[10])(int) = {
    handle, handle, handle, handle, handle, 
    handle, handle, handle, handle, handle, 
};

//--------------------------------------- main program ----------------------------------
int main(void) {

    puts("Terrifiying Concepts of Function Pointers");
    // in the main, we need to set dispath the normal_table to the foo. 
    // the type of normal_table is : array of 10 pointers to a function that takes int. 
    set_dispatch(&normal_table);
    // now that we have foo : foo is just now pointing to the address of normal_table. (because, foo is the pointer to an array of 10 pointers to a function.)
    // now that we need to print the value? how do we?
    printf("0 : %s\n", (*foo)[0](10)); // even 
    printf("5 : %s\n", (*foo)[5](9)); //odd 
    // you knwo that out 

    return EXIT_SUCCESS;
}

