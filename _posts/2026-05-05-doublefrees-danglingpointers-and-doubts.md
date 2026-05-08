---
title: "Some Whys on the UB"
description: "This is about double frees, what happens when you access a freshly declared yet uninit value via a variable. Now that you free the memory, what happens when you access a freed memory? What about freeing two times? double frees. Note that we cannot predict that untill you compile - the compiler does not warn with normal flags, then you run it, boom, why did I encounter a SIGABRT due to a double free?"
type: doubt
tags: [undefined-behaviour, double-frees, dangling-pointers]
---

## Questions

Here I have three unanswered questions about the behaviour of the C code I gave below. Under my attempt to deliberately execute - read uninitalised value, read a dangling-pointer, a use after free and double free, I am confused by the values that are outputed by the C code which was executed. 

**I will be resolving the questions one by one.**

<gh-include src="cobra-r9/Init87/main/misc/practice/error/point2dv2.c"></gh-include>

> But before diving any deeper, there are some important things that I need to understand to resolve my doubts. The Page Table, The Virtual Address Space, what happens underneath - mandatory to understand my first question.

## Question 1 :

> **Why did reading uninitialised values as given below did not give garbage output, but almost always 0?**

```c
    Point point2;
    printf("initx: %d; init y: %d\n", point1.x, point1.y);
    printf("uninit x: %d; uninit y: %d\n", point2.x, point2.y);
    // this one, the above one, always produced by point 2 in this code on my machine is always 0 and 0 respectively. Yet as per C standards is an undefined behaviour.
```

Before getting into this **Why Zero?** stuff, we need to learn what a **Page Table** actually is.

### What a Page Is?

A page is essentially the smallest unit of memory that the operating system manages when *allocating, tracking, and protecting physical RAM*. Rather than tracking every individual byte. Because tracking every individual byte will require enormous bookkeeping overhead and expensive operation as per memory. So what does the OS do?

My Arch Linux does this : 

Group the memory into fixed size blocks called **pages** and manages them as atomic units. On x86_64 Linux, the standard page size is 4096 bytes, or 4KB. But why is there a necessity for the OS to manage this page at all?

**Two Layers: Virtual and Physical Memory**

This is the reason. Every process on a modern OS operates in it's own `virtual address space` - which is a private and contiguous map of address that the process believes represents the real memory. That is, the OS and Kernel together creates an illusion to the process that - there exists a certain amount of memory, that the running process thinks - solely belongs to one itself regardless of the other running processes. 

To put it in other words;
> The process thinks that all the memory belongs only to it and it can utilise any of the address in the virtual address space which is addresses of the virtual ilusion memory provided by the kernel. So, if there are two typical process running at the same time, they both get their own virtual address space to make use of the vast ocean of addresses.

But another doubt arises here.

**What about this? what if the two processes at some point in same time use same address? Would not there be a conflict among the two running processes?**

Answer is NO. Notice that big `O` in the `NO`. This is because these virtual addresses do not correspoind directly to a physical RAM address or locations. Instead, the CPU's Memory Management Unit (aka `MMU`) translates these virtual addresses into physical addresses at the **runtime** - Notice it is not the compile time, but the runtime.

**But how does it do it?** 

So, there exists a structure called the page table. The page table is what helps the MMU to map the virtual addresses of the programs to the physical RAM. Page Table is essentially a mapping : virtual page number to physical page frame number. Each entry in a table also carries the permission bits - the executable, writable, readable - which is how the OS enforces memory protection between the processes and between the user and kernel spaces.





