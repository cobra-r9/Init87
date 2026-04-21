---
title: "Missing Include"
description: "This is a deliberate experiment, intentionally removing the #include headers and trying to call the printf to see what happens."
type: error
tags: [implicit-function-declaration]
---

Here is the exact code what I tried :

<gh-include src="cobra-r9/Init87/main/part1/errors/initv2.c"></gh-include>

Before getting inside, we need to know answer for one question : 
**Why actually the include exists? What it contains? What is it's significance?** (This is one question composed of many question.) 

> When you ask **why?**, it will lead you to a wonderfull location - the location is the **glibc.so** that is a `C` object file.

## What is `#include`?

It is nothing but the C Pre Processor (CPP) command or function or whatever I would like to call, which just as the name indicates, does the copy paste mechanism: find the include : 

1) **\<file.h\>** : First find in the /usr/include directory in the linux file system.

2) **"file.h"** : First search the current directory ./ for the header file, if not present, then fallback to the /usr/include directory for C header file. 

## What actually does `something.h` contains? 

Nothing but the function signatures. The shape of the function. What is a function signature? Each function returns a particular type of value and takes a specific type of arguments and some x number of arguments and have a specific name. So : each function can be described with 4 quantites : 

- return type
- types of arguments 
- number of arguments - directly variadic or non variadic (ie, infinite or non infinte arguments)
- the name of the function 

All these stuffs are designated in the `something.h` header file. 

## So? What does the `<stdio.h>` have to do with `printf`?

As it's name suggests, the `<stdio.h>` (note the < and > opening and closings), it is present in the /usr/include directory, and has the exact function signature (**AKA : function declaration**) for the `printf` function. 

> It is good to note that : `cat /usr/include/stdio.h | grep "int printf"` will return you the function declaration **and not the definition** of the printf function. So, more accurately, the stdio.h only tells the compiler that - **hey : this is how the printf's signature looks like.** and the linux dynamic linker will search for the printf in the glibc.so (GNU C standard library) and fill the holes.

## But which holes? 

Not definitely an $$shole, but the functions : as I said earlier, the assembler will produce an object file : that object file will have an unresolved symbol - printf (ie, a function with unknown definition, but has a signature) - this is the hole in object file produced by assembler. Now, the linux dynamic linker (`ld`) will fetch these holes : link the functions to their definitons from the linux standard library - which is a precompiled object file glibc.so.6 (or whatever depending on your OS).

## Without the include? 

There will be no copy pasta mechanism and hence no signature for the `printf`(in our case). This enables the compiler to **assume the signature of the printf function** - which is known as implicit-function-declaration. (not in `C-23, but in old C`). The compiler will guess a function which returns int and accept any arguments. This is known as implicit-function-declaration - the compiler invents a fake sign.

## So what? Let the compiler guess.

Nope. If that is the case, what would you tell if the compiler guessed a wrong function? What if the signature of the printf function in the glibc.so does not match with whatever the compiler guessed on it's own? 

**Boom! You get an UNDEFINED BEHAVIOR** - wrong stack layout, wrong functions, crashes.

## Is there a way I can use `printf` without `#include <stdio.h>`? 

> **Absolutely Possible.**  Not a surprise because if I am gonna keenly look at the compiler error / warning message (whatever you like to call it as) - say, the compiler's help message - 

```c
note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
```
**or provide a declaration of printf**. Yes, you should provide a declaration of printf, either : copy pasta from the include headers. 

```bash 
cat /usr/include/stdio.h | grep "int printf"
```

You get an output like this : (exactly this)

```c
extern int printf (const char *__restrict __format, ...);
```

And this is what you need to add instead of `include ....`
The below given code resolves the problem : 

<gh-include src="cobra-r9/Init87/main/part1/initv3.c"></gh-include>

### This is the End of this Error Section. 
Good Luck Understanding this. 

