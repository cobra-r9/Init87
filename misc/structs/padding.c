// name : padding.c 
// date : 2026-06-26 
// std  : C 23 standard 
// desc : comparing the struct padding of aligned, unaligned and packed struct. 

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


typedef struct {
    char a; // char is 1 byte 
    long long b; // 8 bytes 
    char c[5]; // 5 bytes 
    int d; // 4 bytes 
    char e; // 1 byte 
    char f; // 1 byte 
    double g; // 8 byte 
    char h; // 1 byte 
    // due to some architectural optimisatoins, the memory is better read when the bytes are read in the blocks of the largest data type(in size. )
    // in this case, the largest size types are double and long long which are both 8 bytes. 
    // therefore the compiler optimises and reads it as set of 8 bytes. 
    // char 1 + 7 padding + ll 8 + string 5 + padding 3 + int 4 + char 1 + char 1 + 2 padding + 8 double + char 1 + 7 padding 
    // so it is 48 bytes. 
    // but actually, striping away the padding, it is just 29 bytes. 
} unaligned_t;

// therefore, the ordering of the fields in the struct matters a lot. we need to align them such that they are in multiple of the largest type in the struct (in this case it is the long long / double)

typedef struct {
    char a;
    char e;
    char f;
    char h; // 4 bytes till now 
    int d; // 4 bytes (here, it is exactly 8 bytes : 1 block)
    long long b; // 8 bytes (2 block )
    double g; // 8 bytes  (3 block)
    char c[5]; // 5 bytes (+3 padding = 4 block)
    // accounting the padding : 4 + 4 + 8 + 8 + 5 + 3 = 32 bytes. 
    // that is it is 16 bytes less than the unaligned_t struct with same fields. 
    // just different order. 
} aligned_t;


// but what if I need it to be tightly packed?
// if not c23 standard, you can use __attribute__((packed)) for packing the struct. 
// else, you can use [[gnu::packed]] in c23. This will tell the compiler not to add padding to the struct, instead pack the struct tightly. 

typedef struct [[gnu::packed]] {
    char a; // char is 1 byte 
    long long b; // 8 bytes 
    char c[5]; // 5 bytes 
    int d; // 4 bytes 
    char e; // 1 byte 
    char f; // 1 byte 
    double g; // 8 byte 
    char h; // 1 byte 
} packed_t; 

// this is destined to be exactly 29 bytes. 

//--------------------------------------- main program ----------------------------------
int main(void){
    

    puts("sizeof different structs in bytes...");
    printf("sizeof(unaligned_t) = %zu\nsizeof(aligned_t) = %zu\nsizeof(packed_t) = %zu\n"\
           , sizeof(unaligned_t)\
           , sizeof(aligned_t)\
           , sizeof(packed_t));
    return EXIT_SUCCESS;
}

// note that the struct alignment is not always 4 bytes (in case of int being the largest type. ). In gerneral, the fields are aligned such that they are read as the multiple of largest type in the struct. (in our case it is double or long long)
