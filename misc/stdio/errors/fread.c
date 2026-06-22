// name : fread.c 
// date : 2026-06-22 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    // open the file : fopen 
    FILE *file = fopen("demo.txt", "r");
    // check if fopen failed. 
    if (!file) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // if it did not failed, proceed reading. 
    char data[1024];
    size_t nmemb = fread((void*)data, sizeof(data), 1, file);
    // read 1024 bytes of data into the buffer data as 1 number from the stream file. 
    // check if all the objects as specified are read. 
    if (nmemb < 1) {
        fclose(file);
        printf("file reading failed.\n");
        return EXIT_FAILURE;
        
    }
    printf("data : %s\n", data);
    return EXIT_SUCCESS;
}

// why did this fail? and return file reading failed?
// ah. the fread failed. because of a partial write. 
// I will explain it in another file. 
