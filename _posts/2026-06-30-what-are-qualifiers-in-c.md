---
title: "Qualifiers in C"
description: "Today, I have discovered the most safe, correct and understandable way for declaring the C types, and something new - qualifiers. What are qualifers?"
type: doubt
tags: [qualifiers, types, attributes]
---

There is this rule called the clockwise or spiral rule in C. The spiral rule is for parsing complex C declarations by alternating between reading right and left around the identifier, spiraling outward. 

### Algorithm 

**Here is the correct method for learning that : How do I parse complex C declarations?**

1) Find the identifier, start there. 
2) Look right - if [] or () is present, then consume it. 
3) Look left - consume whatever is there (*, type, etc.)
4) Keep alternating right - left, spiraling out, until the whole declaration is consumed. 
5) Always, [] and () win over * when both are adjacent (due to precedence), so on the first move you go right if there's a []/() immediately after the identifier - or else, go left. 


**Example on parsing a complex declaration :**

```c 
char *(*(*foo)[10])(int);
```

This for me, initially seemed to be an impossible type, then I realised that it is : in fact possible. 

1) identify the identifier which is **foo**
2) immediately right of the identifier there is this **closing parenthesis** ')'.
3) therefore, we need to bound them as a whole : `(*foo)`
4) left of the identifier is the *: therefore **foo is a pointer to ...**
5) look the next right of `(*foo)` which is `[10]`, an array of 10 : **foo is a pointer to array of 10 ...**
6) look the left of `(*foo)[10]` which is again another pointer : **foo is a pointer to an array of 10 pointers to ...**
7) look the right of `*(*foo)[10]` which is another ')' : so we need to bound them as a whole. 
8) look the left of `*(*foo)[10])` which is another '(' : therefore, we need to consider as a whole to `(*(*foo)[10])` : That is **foo is a pointer to an array of 10 pointers to ...**
9) look the right of `(*(*foo)[10])` which is an `(` : therefore, we need to evaluate that paren till its bounds end. 
10) `(int)` is where the paren closes. : **foo is a pointer to array of 10 pointers to a function that takes in integer ...**
11) immediately left of `(*(*foo)[10])(int)` there is this char* : **foo is a pointer to an array of 10 pointers to a function that takes in an integer and returns a pointer to char.**

I have added additional steps complicating the paren. **paren means : just give and group it.**

### Some other examples. 


These are relatively simple qualifiers as compared to the previous one. 
Read it backwards (as driven by Clockwise/Spiral Rule):

- `int*` - pointer to **int**
- `int const *` - pointer to **const** **int**
- `int * const` - **const** pointer to **int**
- `int const * const` - **const** pointer to **const** **int**

Now the first `const` can be on either side of the type so:

- `const int *` == `int const *`
- `const int * const` == `int const * const`

If you want to go really crazy you can do things like this:

- `int **` - pointer to pointer to **int**
- `int ** const` - a **const** pointer to a pointer to an **int**
- `int * const *` - a pointer to a **const** pointer to an **int**
- `int const **` - a pointer to a pointer to a **const** **int**
- `int * const * const` - a **const** pointer to a **const** pointer to an **int**
- ...

If you're ever uncertain, you can use a tool like cdecl+ to convert declarations to prose automatically.

To make sure we are clear on the meaning of `const`:

```c
int a = 5, b = 10, c = 15;

const int* foo;     // pointer to constant int.
foo = &a;           // assignment to where foo points to.

/* dummy statement*/
*foo = 6;           // the value of a can´t get changed through the pointer.

foo = &b;           // the pointer foo can be changed.



int *const bar = &c;  // constant pointer to int 
                      // note, you actually need to set the pointer 
                      // here because you can't change it later ;)

*bar = 16;            // the value of c can be changed through the pointer.    

/* dummy statement*/
bar = &a;             // not possible because bar is a constant pointer.           
```



`foo` is a variable pointer to a constant integer. This lets you change what you point to but not the value that you point to. Most often this is seen with C-style strings where you have a pointer to a `const char`. You may change which string you point to but you can't change the content of these strings. This is important when the string itself is in the data segment of a program and shouldn't be changed.

`bar` is a constant or fixed pointer to a value that can be changed. This is like a reference without the extra syntactic sugar. Because of this fact, usually you would use a reference where you would use a `T* const` pointer unless you need to allow `NULL` pointers.
