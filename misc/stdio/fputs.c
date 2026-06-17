// name : fputs.c 
// date : 2026-06-17 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {

    // open the file buffer. 
    FILE *file = fopen("demo.txt", "w");
    if (!file) {
        perror("fopen failed : ");
        return EXIT_FAILURE;
    }

    // the fputs signature : fputs(const char *buffer, FILE *stream);
    // on error, it returns a negative value. on success, it returns a meaningless, non negative value. that's it. 
    int return_value = fputs("this is a message from the fputs.c\n", file);

    // if the return value is less than zero, then it impolies, that the fputs failed, 
    // perror it. 
    // then close the file. 
    // return it as failure. 
    if (return_value < 0) {
        perror("fputs failed : ");
        fclose(file);
        return EXIT_FAILURE;
    }

    // also, even if it succeeds, never forget to close the file stream. 
    fclose(file);
    return EXIT_SUCCESS;
}

