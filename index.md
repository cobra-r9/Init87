---
layout: default 
title: "Init87" 
description: "A learning phase to completely internalise the very essence till the memory of C. Not for mere job, but just to understand why C is C and why C runs the way it runs. Not a surface work anymore. I treat every piece of C code as a potential vulnerable and exploitable code. This is the first file in my journey."
---

# What this is - My Journalctl for C

Let's start with. This is my personal C learning phase soon before entering into the college during my holidays. I fine tuned this pathway for me not just to get a job, but involve in national technical research matters. I have an obsession, from the very beginning when I first started to type a `<html>` in my grade 7. But over years, it accumulated towards - linux systems, kernels, exploits and leverage. While wondering **how do I actually get into this?**, C provided me answer with [STUXNET](https://en.wikipedia.com/wiki/stuxnet). That is the first thing in field of low-levels and malwares that literally caused me goosebumps - not the destructive potential, but the way it was engineered to rootkit a PLC board in Simens Controller. Let's leave about me, get into C. This is not for you to learn, but for me to document my journey to decomposing STUXNET. (I think, that should be possible in a 5 year time window - maybe.)

## Preparing the Master Index

It took a good amount of time for me to investigate and find a starting point. After roaming into **kali** at grade 10, **parrot** by the end of the year, only to realise I need to learn it instead of passively consuming stuffs. Now, it has been **one year** since I started daily driving **Arch Linux** - *for the sake of understanding linux internals*, the [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)), and some of basic school python. Then after a great realisation that my passion is towards - low level stuffs, I started to search for an irreplacable programming language - **rust**, then fall back to **C** to understand what actually *rust prevents you from*. It has been a month since I started learning C - with the principle of **doing a biopsy** on C. Searched web, provided some pdfs and asked claude to generate a good master index for C.

But I was pretty unsatisfied with the depth and made my own modifications in the master index. To be frank, the master index is only one of many indexes I made for learning C and making the journey as chilling as possible. This only covers **what I consider as basics**. Never ends anyway.

If you want to check out my master index for basics - here is the [basics-master-index](./pathway/01-basics.md)

> This is not some course you are going to encounter in random unacademy or coursera. It is my journey of learning C. And this is a **documentation** of my journey.

## Journey Structure?

Well. This is the most exciting part. For now, Init87 only focuses on **whatever I consider is the basics for my final long term goal**. You may encounter some random partially understood (I mean, just one part) of assembly or disassembly, and most of inline comments in my main branch's code(that is full of code to inspect, practice, etc), with errors documented - why should that error happen - and alonside with on the way experimentation.

> Fear not a man how does 1000 different kicks, but someone who does the same kick for 1000 times. - *Master Bruce Lee*

So yes. Especially in this **Age of AI (or whatever ultron)**, for what I expect - not possible to learn all at once, but possible to build depth and components for learning them later. C -> Assembly -> C++ -> Rust. So obvious, C has more to do with. 

Each part of my index would have a submodules. Eg, part 1 will have 1.0, 1.1, etc. In my `main` codebase github branch, each of it would have:

- Seperate dedicated directory.
- Each directory will be having a errors directory.
- It has an assembly directory if I were to analyse any section of memory.
- With each file having inline comments. 

## Where to Start With?

Well, there are **two simultaneous branches**. 

1) Basics branch

Deals with whatever I have in my [basics-master-index](./pathway/01-basics.md) - essentially the *basics of C*, starting from it's history. 

2) Memory Branch

Deals with the *memory side of C* - whatever I have in my [memory-master-index](./pathway/02-pointers.md), starting from what a ram actually is, leading to the ultimate `malloc, calloc, etc` - i.e, the manual memory management side of C programming.

> Some parts of Basics and Memory Branch may overlap, but for gods sake, they are in different approach. One deals with literal C, the other deals with memory layout.

## Code Base 

Instead of just keep documenting, I usually write code in my `main` branch, by default, have inline comment explaining the code, theory from many books, and ask AI to document the exact theory with web references and verifications. So what actually matters for me is not the theory, but the **code base**. I am a bit philosophical - let me pull up a quote what is currently in my mind after typing this statement - 

> Practice makes a (wo)man perfect.

## Tip of Iceberg 

Best practices - start with the [basics](./pathway/01-basics.md) and go as per order. Even history is important - and sites **stuxnet** as example - kinda some inspiration.
