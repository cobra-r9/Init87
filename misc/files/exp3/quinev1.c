// the most basic quine in C; capable of constructing its own code from scratch only using pure logic and string formatting. 
// file : quinev1.c 
// desc : just for experimentation purposes. 
// first we would have to include the C standard library. 


// if we need, we can also include comments, but that requires a couple of 10s and 9s to be formatted. 
#include <stdio.h>

// then int main(void) main returns a type int and takes 0 args. though void is not necessary in modern c23. 
int main(void) {
  // here comes the fixed point in the quine. this string is literally the program itself ,but capable of self constructing using string formatting. 
  // we use the ascii codes here : 34 - for the double quotes. 
  // 10 for newline \n and 9 for a tab character \t. 
  // that's it, logic follows the remaining stuffs. 
	char *s = "#include <stdio.h>%cint main(void) {%c%cchar *s = %c%s%c;%c%cprintf(s, 10, 10, 9, 34, s, 34, 10, 9, 10, 9, 10, 10);%c%creturn 0;%c}%c";

  // main print to print the source code to the output. 
	printf(s, 10, 10, 9, 34, s, 34, 10, 9, 10, 9, 10, 10);
  // finally return the code. 
	return 0;
}
