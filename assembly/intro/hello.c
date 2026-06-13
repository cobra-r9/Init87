// name : hello.c 
// date : 2026-06-13 
// std  : C 23 standard 
// desc : replicate the assembly hello.s 

//---------------------------------- include header files -------------------------------
#include <unistd.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    write(1, "Hello Assembly!!!\n", 18);
    // though we need to check if write succeeds or not using its return value, I know it will succeed, so avaoid it. 
    // 18 here is the length ie the size of the string.
    return 0;
    // the return code.
}

