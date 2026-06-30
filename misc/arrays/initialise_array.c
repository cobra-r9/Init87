// name : initialise_array.c 
// date : 2026-06-30 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Initialise Array\n");
    // We can create a multidimensional array. 
    // consider them as matrix. 
    // case : nxm : rowsxcolumns

    // and this is a I3 matrix. 
    int matrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };

    // outupt it by looping over the rows and columns.
    puts("Identity Matrix : ");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}

