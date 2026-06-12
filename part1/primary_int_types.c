// name : primary_int_types.c 
// date : 2026-06-12 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> // has CHAR_BIT 

// therefore for getting the size of the data type in bits, we can multiply the CHAR_BIT with the sizeof(type).

//--------------------------------------- main program ----------------------------------
int main(void) {
    // there are 5 primary int types. 
    // char, short, int, long, long long. 
    // in x86_64, char is 1 byte, short is 2 bytes, int is 4 bytes whereas long and long long are 8 bytes.
    // but the c standard itself does not gaurentee you that 1 byte is equal to 8 bits. 
    // it can be accessed from the <limits.h> via CHAR_BIT, which is a macro defined there.
    // it specifies the number of bits in a char. 
    // let's define some variables 
    char a = 66; 
    short b = 125;
    int c = 213423;
    long d = 89232332;
    long long e = 99999999999999;

    printf("The values of : \nchar = %c\nshort = %hd\nint = %d\nlong = %ld\nlong long = %lld\n\n", a, b, c, d, e);
    printf("The sizeof on the primary int types : sizeof(char) = %zu\nsizeof(short) = %zu\nsizeof(int) = %zu\nsizeof(long) = %zu\nsizeof(long long) = %zu\n\n", sizeof(a), sizeof(b), sizeof(c), sizeof(d), sizeof(e));

    printf("Alright : %c\n", 65);
    // this is gonna print A. because the 65 is ascii value of A, having same bytes. 
    // information = bits + context. 
    // both A and 65 have same byte stream, but the context differs.
    // in case I use %d instead of %c, we get this : 65 itself.
    printf("Integer? : %d\n", 65);

    // in my current system, here is the char_bit 
    printf("CHAR_BIT : %d\n", CHAR_BIT);
    // in most x86_64 systems, it is 8; 

    return EXIT_SUCCESS;
}

