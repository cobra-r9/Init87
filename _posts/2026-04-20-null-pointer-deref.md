---
title: "Dereferencing NULL gives SIGSEGV, not zero"
description: "Assumed *ptr would just be 0 if ptr was NULL. It segfaults."
type: error
tags: [pointers, segfault, ub]
---

Tried this:

<gh-include src="cobra-r9/Init87/main/part1/errors/initv2.c"></gh-include>

This is just a demo code. Don't worry to check if everything is alright. Alright.
