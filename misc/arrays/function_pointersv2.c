// name : simplified_function_pointers.c 
// date : 2026-07-01 
// std  : C 23 standard 

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


// here is where typedef comes to help. 
// foo : a type that denotes a pointer to an array of 10 pointers to a function that takes int and returns a pointer to char.
// call it the pointer_data.
typedef char* (*(*pointer_data)[10])(int);

// now define the variable foo; which is of type : pointer_data
pointer_data foo = NULL; 
// note, this is a single opinter to an array of 10 pointers to function that takes int and returns char. 


// now we need a function which takes the pointer to an array of 10 pointers to a function that takes int and returns a pointer to char, and we set it to foo. all it the set_table function. 
// it returns nothing.
// see? very simple?
void set_table(pointer_data table) {
    foo = table;
}

// the same handle function :
// as set in the modern c book, always ALWAYS keep the identifier seperate from the type. 
char* handle(int code) {
    if (code % 2 == 0) {
        return "OK";
    } else {
        return "ERROR";
    }
}

char* dehandle(int code) {
    if (code % 2 != 0 ) {
        return "OK";
    } else {
        return "ERROR";
    }
}

// now we define that beast table. 
// what is the type of that table? , less, it is not a pointer, but an array. 
// an array to a 10 pointers to functions that take int and return pointer to char. 

char* (*normal_table[10])(int) = {
    handle, handle, dehandle, dehandle, dehandle,
    handle, dehandle, dehandle, handle, handle,
};

//--------------------------------------- main program ----------------------------------
int main(void) {

    puts("Take the same code. from v1");
    set_table(&normal_table);
    printf("function index 0 @ value = 10 : %s\n", (*foo)[0](10));
    printf("function index 7 @ value = 20 : %s\n", (*foo)[7](20));
    return EXIT_SUCCESS;
}

