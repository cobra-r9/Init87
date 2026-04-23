---
title: "Everyting About Bytes and Endianess"
description: "What exactly is a byte? How is the memory addressed by the CPU processor to execute stuffs? What is the reading format? How is it represented? Here are the answers for all these questions. Bit of a theory."
type: doubt
tags: [address, endianess, memory]
---

## The Model 

In computer systems, memoryis logically organised as **linear array or bytes**, where each byte is the smallest addressable unit. 

> You heard that right. Though bits exists, and arch dependent, 8 bits is 1 byte. Why can't a processor read it as bit by bit instead of a byte? Later.

This conceptual model is referred to as virtual memory, presenting the program with a single, monolithic array of bytes regardless of the underlying hardware implementation.

## What is the fundamental memory organization?

Here are some terms that are mandatory to learn before getting into the theory.

1) **The Address:** Every byte of memory is identified by a unique number known as its address, which acts as an index into the large byte array. Byte array? it is just a linear arrangement of several bytes.. and remember, not always a byte equals 8 bits. It is arch dependent and may not be true in striped embedded systems.

2) **Virtual Address Space:** Fun fact. Even if your physical ram is 8 GB in size, yet you exist in a 32 bit arch, then, you can never directly utilise all of your 8GB RAM. Why? because, when a program runs, your OS, Kernel and Memory, together creates a virtualisation, an illusion for the process that it is the only process which runs in the system and has full access to memory. In reality, the memory is shared among different processes. But how the heck is that possible? It is all because of a virtual memory space, which randomly maps to physical memory. And this virtual memory has address for each byte. That is what we call the Virtual Address Space.

> More technically - The set of all possible addresses available to a program is its virtual address space. The size of this space is determined by the system's word size. For a system with a `k-bit` wordsize (remember? the 32-bit, 64-bit wordings?), virtual addresses can range from 0 to 2<sup>k - 1</sup>, allowing the program to access up to 2<sup>k</sup> bytes (in address, not in physical ram)! That is **16 Exabytes of virtual memory space in a 64-bit arch!**

3) **Machine Level Perspective:** At the machine level, the processor views memory purely as a byte addressable array. Unlike the high level languages, the machince code knows only **bytes**. And literally there is no way to distinguish which 0 is an integer and which 1 is a character. Then how is what we need achieved? It simply maipulates bytes at specific address.


## What is Multi-Byte Object?

In C, a data type does not simply take one byte alone. It may span across multiple bytes to just accomadate that value. Why? It is used for an act of differentiation of the different data types. For example, the 

- `sizeof(int)` in `32,64-bit` respectively are each `4 bytes` whereas,
- `sizeof(int *)` in `32,64-bit` respectively are `4,8 bytes` respectively.

Such datatypes are not like `char - which is 1 byte`, but span multiple bytes. How are these data stored?

**This is how I visualize it**

> As learnt in the earlier part of the theory in my self learning phase, I can assume each bit to be one box. Note that this **bit box** does not have any address marked in it. In 32, 64 bit archs, a group of 8 bits is linear and joint as a long rectangle, but all attached boxes. This long **rectangle** is a single byte. And, this **rectangle** has overall an address. This is the address of that particular byte in Virtual Address Space.

**Contiguity:** In virtually all machines, a multi byte object is stored as a contiguous sequence of bytes - the long rectangles. An int type in 32, 64 will be 4 long rectangles with each rectangle having some address (virtual) like `0x100, 0x101, 0x102, 0x103`, the rect seq ends and int data ends here at last byte. 

> So, a int number 44 is stored across 4 bytes spread as charges - electrons in each box, if charge present, in each square bit, it is 1, else 0, and a specific charge configuration in memory makes up the data 44, and this takes 32 bits - ie, 32 such individual charge states.


## Original Address?

Ok, here comes another question. There are 4 address for a data type such as int, which of those 4 address should be considered as address of the integer? 

**This is known as the identifier address.** As name suggests, this address is what used to identify the data stored. The block of 4 rectangles - unsurprisingly, this address points to only one of those 4 rectangles. It points to the **smallest address** among those all bytes, ie those boxes.

> More intuitively, as I know how I understood it, consider each rectangle to be a compartment of train. But one of those compartment is definitely the engine of the train. Each compartment would and must have sequential number labels. The engine has the lowest value label. You then address the train using the label of the engine. Here : each compartment = 1 byte. A train = 1 piece of data : whatever - int, char, pointer, string, array, etc. To address the data - i.e, to point to the data, you call out to the train engine - **smallest address**.

**Pointers?**

In C, the value of a pointer is simply the address (virtual essentially) of the train engine. i.e, the first box of the storage holding the object it points to.

## How? Then Mapping Virtual Mem to Physical Ram?

The address used by a program are virtual addresses, which must be translated into physical address (mapped) before the data can be retrived from the actual DRAM. This task is performed by the **Memory Management Unit(MMU)**.

- MMU resides on the CPU.
- This mapping thing is done by the MMU using lookup tables - page tables managed by the operating system.
