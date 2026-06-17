// name : fwrite.c 
// date : 2026-06-17 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <stdcountof.h>
#include <errno.h> 
#include <string.h> 

//--------------------------------------- main program ----------------------------------
int main(void) {

    errno = 0;

    FILE *file = fopen("../fwrite.txt", "w");
    if (!file) {
        perror("fopen failed : ");
        errno = 0;
        return EXIT_FAILURE;
    }

    const char buffer[] = "hello from fwrite\n";
    printf("sizeof(buffer) : %zu\nstrlen(buffer) : %zu\ncountof(buffer) : %zu\n", sizeof(buffer), strlen(buffer), countof(buffer));

    int return_value = fwrite(buffer, sizeof(buffer[0]), countof(buffer) - 1, file);
    // countof(buffer) - 1 to exclude the trailing null terminator. 

    if (ferror(file) || (unsigned long)return_value < countof(buffer)) {
        perror("fwrite failed.");
        clearerr(file);
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);


    return EXIT_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------- 
/* Exact error message produced. I found the answer why this error happend (though it is just a bug.) (forgot a - somewhere?)

sizeof(buffer) : 19
strlen(buffer) : 18
countof(buffer) : 19
fwrite failed.: Success
make: *** [/home/cobra/.local/bin/cenvs/Makefile-default:9: run] Error 1

*/
