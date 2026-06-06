// the code involves the code from the getting-started in C in modern C book.
// this is a comment.
// we would have to include 2 header files for the purpose.
// the C standard input output library for printf
#include <stdio.h>
// the C standard library for exit codes EXIT_SUCCESS
#include <stdlib.h>

// instead of writing the code as the follows
// int main(void) { ... }, we will be explicitly getting argc and argv.
// but tell the compiler that we might not use that argument.

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[argc + 1]) {
    // declare a array, and set its value explicitly.
    // the array type is of a double
    // we are leaving the 3rd and 5th and 6th index unset, which is zero.
    double A[6] = {
        [0] = 0.99,
        [1] = 0.88,
        [2] = 1.0e9,
        [4] = 20.0e-9,
    };

    // the format specifier of typeof(i) is size_t's specifier : %zu
    // we loop until 0 is less than 6.
    // which means, first the program rungs, i is at zero , it evaluates A[0],
    // does stuffs and finally does this : ++i; that is, it icrememnts iteself,
    // then returns itself. this happens until i is 5 : 0 to 5 is 6 elements, all
    // of that double array A are printed.
    for (size_t i = 0; i < 6; ++i) {
        printf("%zu : square(%g) = %g \n", i, A[i], A[i] * A[i]);
        // in the output, the e9 and e-9 notations are converted automatically into
        // scientific format : a.xx * eb
    }

    return EXIT_SUCCESS;
}
