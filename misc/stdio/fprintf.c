// name : fprintf.c 
// date : 2026-06-17 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {

    // open a file buffer in write mode. 
    FILE *file = fopen("hello_via_fprintf.c", "w");
    // conduct file checks. 
    if (!file) {
        perror("fopen failed : ");
        return EXIT_FAILURE;
    }

    char *payload = "#include <stdio.h>%cint main(void){%c%cprintf(%chello, world!\\n%c);%c%cprintf(%cThis code is written from fprintf via formatters. lol.\\n%c);%c}%c";
    // \n, \n, \t, ", ", \n, \t, ", ", \n , \n 
    // 10, 10, 9, 34, 34, 10, 9, 34, 34, 10, 10 : format ascii. 
    // lol, seems like obfuscation? but it is string formatters. hua!

    // alright, if it did not fail, here we are to the writing part of the file IO. (non syscall.)
    // fputs and fprintf : these are the unformatted and formatted cousins of puts and printf, except that these write to a file stream, whereas the latter writes to stdout. (fd = 1;)

    // function signature of fprintf : int fprintf(FILE *stream, const char *fmt, ...);
    // return type of fprintf : int type, returns the actual number of bytes that is written. 
    // this is useful. for example we can compare the sizeof formatted string vs the bytes written. It stops at null terminator, that is not written. 
    // -------------------------------------------------[doubt 1] : is it?
    // How do I literally check if the fprintf wrote everything? and not partially?
    // we shall learn more about error handling later on. 

    int return_value = fprintf(file, payload, 10, 10, 9, 34, 34, 10, 9, 34, 34, 10, 10);
    // on failure, the fprintf returns a negative value. we can compare it to do a primitive check on it. 
    if (return_value < 0) {
        perror("fprintf failed : ");
        fclose(file);
        return EXIT_FAILURE;
    }

    // never forget to close a file. 
    fclose(file);

    // come one, the power of my system on me!!!.
    if (return_value > 0) {
        system("gcc hello_via_fprintf.c -o out && ./out && rm out");
    }

    return EXIT_SUCCESS;
}

