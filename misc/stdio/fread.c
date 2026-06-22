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
    // in this case, soon after the file reaches the EOF, the read ends. 
    // that is : the file size is less than the buffer allocated. 
    // it reaches EOF even before 1024 bytes. 
    // therefore it is considered a partial read, thouh all the data is read from the file.
    // the below given check is only for : if it not at all read. 
    if (nmemb == 0 ) {
        printf("fread failed.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("data : %s\n", buffer);

    return EXIT_SUCCESS;
}

// why did not this work too?
// this is because : the file has less objects than that of 1024. 
// as a result, I should nor be considering nmemb < sizeof(buffer) in case the size of file is actually less than the objects read. 
// instead we should be comparing if : nothing was read. 

// this time, partial read is ok. but what if I have partial write actually when the sizeof the file is exactly equal to the buffer size?
// how do I find it?
// sometime partial writes are OK. 
// but how do I?
// what if it were a real partial write?
// -----------------------------------------[doubt]
