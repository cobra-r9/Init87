// name : fopen.c 
// date : 2026-06-17 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {

    FILE *file = fopen("file-not-exist.c", "r");
    if (!file) {
        perror("fopen failed! figure out why.");
        // perror states : No such file or directory.
        // this statement is provided from the inference of errno set by the fopen.
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

//---------------------------- analyse the error and what is happening under this function 
//-- in errors/ of the Init87
