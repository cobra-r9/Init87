// name : argc.c 
// date : 2026-06-13 
// std  : C 23 standard 
// desc : introduction to C arguments.

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
// this is a main program, which instead of a void as argument, has argc and argv.
// argc is of integer type, which is the length of the array.
// argv is array of strings. type char**; but we also denote it as *argv[]; 
// note the difference : char argv[] = "some mutable string."
// char *argv[] = {"immutable", "immutable", "immutable"}; but the array as a whole is mutable.
// or char **argv = {"str1", "str2", "str3"}
// argc = length of the array;
// index of array starts at zero, so basically has argc + 1 indices.
// it is up to us to specify the indice inside the array or not.
int main(int argc, char *argv[argc + 1]) {

    // now that we will print how many arguments are there.
    printf("number of arguments : %d\n", argc);
    printf("the first argument : %s\n", argv[0]);

    // from the output, we can always see that the first argument is always the name of the command.
    // what happens if we try to access the next argument even if it is not provided?
    printf("the non existent second argument : %s\n", argv[1]);
    // alright. In C 23, it says (null)
    // let's go further by verifying the stuff.
    if ( argv[1] == NULL ) {
        printf("Yes, it is null!\n");
         
    }
    // but is it possible for us to assign argv values? like 
    argv[1] = "some value";
    // print it?
    printf("after assignment : %s\n", argv[1]);
    // but what? How was this possible? I can assign values myself? hua?
    // but wait.
    // argc = 1 : that is the size of the arguments; Only one is there which is the binary name itself.
    // argc + 1 means the length of the array is actually 2 regardless.
    // and argv[0] = ./binary_name 
    // argv[argc] = argv[1] = null;
    // and I can write to a null value. because it is staill valid.
    // how? because the length of the array was never out of bounds.
    // essentially : *argv[argc + 1] = { "./binary_name", NULL };
    // but can I actually overwrite a null value just like this?


    // try with argv[2]
    printf("the non existent third argument : %s\n", argv[2]);
    // interesting. The read succeeded. But see the result?
    // the non existent third argument : MEMORY_PRESSURE_WRITE=c29tZSAyMDAwMDAgMjAwMDAwMAA=
    // what the hell is this variable? seems like env variable.
    // trigger a sigsegv; lets try writing to that variable. MEMORY_PRESSURE_WRITE. 
    argv[2] = "MEMORY_PRESSURE_WRITE=I-modified-it!!!";
    printf("the non existent third argument again: %s\n", argv[2]);
    // Hell and it is modified. It is ok and just working though undefined?
    printf("the 4th argument: %s\n", argv[3]);
    // so basically I am mining the data that is out of bounds of this argv, there is another array of strings, like essentially variables. The value of it is :
    // the 4th argument: SRC=argc.c (esseitnally this file name.)
    printf("the 5th argument: %s\n", argv[4]);
    // I cannot just accempt this!!!! See the next 10 in the memory, they are essentially my env variables.
    for (int i = 0; i < 70; i++) {
        printf("the %dth argument: %s\n", i + 6, argv[i + 5]);
    }
    argv[75] = "SHELL=/bin/bash";
    system("alacritty");
    // alright, usually, my alacritty will open up in a fish shell prompt. here it is a bash prompt lol. because I have inline modified the shell environment variable. I could not get past this variable. it segfaulted past argv[76]
    // And currently, I don't know what just happened to be overwritten.
    return EXIT_SUCCESS;
}


// all doubts regarding this will be clarified in the doubts section.
// I pretty sure have no idea what was overwritten and what was past argv?
