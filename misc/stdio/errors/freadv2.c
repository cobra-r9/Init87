// name : fread.c 
// date : 2026-06-22 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {

    FILE *file = fopen("demo.txt", "r");
    if (!file) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    // we have now created an empty buffer of size 1024 bytes. 
    // but for sure the size of the file : demo.txt is gonna be less than that. 

    // here we go with the fread :
    // fread will try to read a single object of size 1024 when we say : fread(data, sizeof(data), 1, file);
    // but as our file is not exactly 1 mb, 1024 bytes are not written. and there is only partial write. 
    // what a bug? how to fix it? 
    // we can read 1024 items of size 1 byte : that is sizeof(char).
    // by doing this, we can prevent partial write. 
    // but still I have a doubt. How can we read 1024 objects when the file has only fewer objects?
    size_t nmemb = fread(buffer, sizeof(char), sizeof(buffer), file);
    if (nmemb < sizeof(buffer)) {
        printf("fread is partial read.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("data : %s\n", buffer);

    return EXIT_SUCCESS;
}

// why did not this work too?
