// name : fwrite.c 
// date : 2026-06-17 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <stdcountof.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    // always initialise the errno with 0; 
    errno = 0;
    // here we are : in my favourite file writing companion : the fwrite. 

    // first we would have to open a file buffer and do the normalians stuff. 
    FILE *file = fopen("fwrite.txt", "w");
    if (!file) {
        perror("fopen failed : ");
        return EXIT_FAILURE;
    }
    // if the stuff is not to be return exited. 
    // then we might need to reset the errno 
    // errno = 0;
    // else continue the fwrite. 
    // function signatue of fwrite : size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream);
    // --------------------------- doubt 1 : what is that thing restrict? popping in most of the declarations?
    // semantics : 
    // this writes nemeb objects, each of size bytes from the ptr to the stream. The total byte count attempted is size * nmemb. 
    // both are size_t, 4 bytes, same as int, and overflow is possible if both are sufficiently large files. 

    // return value : 
    // on success it returns the nmemb : the number of members written. 
    // on partial write or error : return value < nmemb 
    // if size == 0 or nmemb == 0, then it returns 0, it no error set, or no IO attempted. essentially writing 0 bytes of 0. 
    // consider maths : it is essentially an empty set. 

    // note : the return value is nmemb and not size. it does not tell us how many bytes are written, instead how many members are completely written. 
    // for more details do man 3 fwrite in case you use linux. 

    char buffer[] = "hello from fwrite\n";
    // there exists a function called countof() in the lib : stdcountof, which only works for the arrays - which will tell us the number of elements in the array. 
    int return_value = fwrite(buffer, sizeof(buffer[0]), countof(buffer) - 1, file);

    // here I reduced the nmemb less that what it is because : 
    //              what actually here is the last member is the null terminator. Which we don't need. 
    // or we can write the entire array one time : 
    // int return_value = fwrite(buffer, sizeof(buffer), 1, file);

    // this is literally equivalent to : &buffer[0] = buffer : all the same - just pointer decay. 
    // and buffer[1] = *buffer : again - dereference the pointer points to the first element. 
    // buffer : the same as &buffer[];
    // but it does not communicate via errno, but wite ferror. if the ferror is set, then it impiles there is an error. 
    // we also need it to exit if it did not write the elements.
    // we also need to cast the return_value to long unsigned. (well in integer territory : int).
    // cannot cast countof because it may risk truncation.

    // ---------------------- doubt 2 : does fwrite also include the null terminator?

    // the anser is : it depends. everything is on the size_t size. sizeof(buffer) is 19 including null terminaotr. We should do strlen(buffer) instead. (this is the case when we follow the case 2 : when we write it as a whole.)
    if (ferror(file) || (long unsigned)return_value < countof(buffer) - 1) {
        perror("fwrite failed : ");
        // telss us why the fwrite failed if errno were set. (clear errno before fwrite is called. )
        clearerr(file);
        // this one clears the error indicator of the file stream. 
        fclose(file);
        return EXIT_FAILURE;
        
    }

    // close 
    fclose(file);

    return EXIT_SUCCESS;
}

