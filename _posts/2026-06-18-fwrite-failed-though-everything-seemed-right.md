---
title: "A bug or something? - fwrite failed."
description: "This is where most class of other bugs appear. When you miss something very small in the logic. And this page will explain what it is."
type: error
tags: [perror, stdio, fwrite]
---

## fopen and analysis

**Here is the exact code what I wrote :**

You may try to figure out what the error is in this code. Why did my `fwrite` produce error stating `Success`.

<gh-include src="cobra-r9/Init87/main/misc/stdio/errors/fwrite.c"></gh-include>



## The corrected code. 

**Add a symbol there - `fwrite` has been my favourite**
<gh-include src="cobra-r9/Init87/main/misc/stdio/fwrite.c"></gh-include>

