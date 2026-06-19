---
title: "A bug or something? - fwrite failed."
description: "This is where most class of other bugs appear. When you miss something very small in the logic. And this page will explain what it is."
type: error
tags: [perror, stdio, fwrite]
---

# fwrite and my code 

**Here is the exact code what I wrote :**

You may try to figure out what the error is in this code. Why did my `fwrite` produce error stating `Success`.

<gh-include src="cobra-r9/Init87/main/misc/stdio/errors/fwrite.c"></gh-include>

## What fwrite actually is?

Below given is the function signature of `fwrite` - i.e, it's declaration. 

```c 
size_t fwrite(const void *prt, size_t size, size_t nmemb, FILE *stream);
```

It doesn't write **size bytes** - it writes `nmemb` elements, each `size` bytes wide. Internally it treats the memory block as `size *count` bytes and write them sequentially as if calling `fputc` for each byte. The return value is not a byte count - it's the number of complete elements successfully written. If that returned count is less than the `nmemb`, a writing error prevented completion and the stream's error indicator (not `errno`) gets set. 

> It is important for us to note that **`errno` may or may not be set**, but it is the **error indicator** of the stream that is get set. Stream? What stream? the FILE stream. It is a struct which has all this relevant field for setting errors. And this error can be **accessed via `ferror`**.

Therefore, the *idiomatic* check is `ferror(stream)`, not just comparing the return value. That is why I added the *comparison* alongside the `ferror` check and it turns out the actual bug was in that comparison. `ferror` was not set. It is good to go with `ferror` alone for most cases. But if you know for sure that - *The exact number of nmemb are the ones written and you are comparing them*. So remember that `ferror` is the one that actually is gonna tell us whether it is actually an error vs (size of nmemb being zero for example.)

## What exactly is happening under hood 

Here we are stepping into the `glibc` part. 

## The corrected code. 

**Add a symbol there - `fwrite` has been my favourite**
<gh-include src="cobra-r9/Init87/main/misc/stdio/fwrite.c"></gh-include>

