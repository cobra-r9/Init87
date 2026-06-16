---
title: "Snprintf Analysis Doubts"
description: "This section involves the three doubts which I encountered while learning about what is happening under snprintf formatting and memory allocation."
type: doubt
tags: [wformat-truncation, warning]
---

## `snprintf`

This is the function signature of the `snprintf` function.

```c 
snprintf(char *buf, size_t maxlen, const char *format, ...);
```

It takes a buffer to write to, size_t of maximum length of string to write, and the format, followed by the format strings (...).

**Return Value :**

(from : `man 3 snprintf`)

Upon successful return, these functions return the number of bytes printed (excluding the null byte used to end output to strings).

The function `snprintf()` do not write more than size bytes (including the terminating null byte ('\0')).

If the output was truncated due to this limit, then the return value is the *number of characters (excluding the terminating null byte) which would have been written to the final string if enough space had been available.*  Thus, a return value of size or more means that the output was truncated.

On error, a *negative value is returned*, and `errno` is set to indicate the error.

**Here is the exact code what I tried :**

<gh-include src="cobra-r9/Init87/main/misc/stdio/snprintfv1.c"></gh-include>

## My doubts : 

### Doubt 1 : 

**Does the `snprintf` take into the account other null terminators also while doing the formatting?**

For example, in this place (line 41)

```c 
char *name = "two";
char buf[8];
snprintf(buf, sizeof(buf), "%s %d", name, 123);
```

Considering the null terminator of the name : it is 4 bytes. 
Considering the Space in formatting it is +1.
Considering the numbers it is another +3 bytes. 
So total It is 8 bytes?

**Answer :**

Nope. I considered it wrong now. While formatting, the format enabled functions like `snprintf` and `sprintf` do not consider any null terminators if any strings were involved in the formatting, but instead only append a single null terminator at the end of the format.

**It is also important to note that :** The null terminator would take 1 byte extra; that is the actual size of the string being written is `length of string * sizeof(char) + 1` which is essentially `length of string + 1`

Therefore, the null terminator from the `name` char pointer is not considered under formatting. Instead, the 8th byte comes from the null terminator `\0` which is added by the `snprintf` itself during the formatting. 

**We can generalise the result as the following :**

- If there were n strings involved each of variable length l1, l2, l3, .. ln, the size of each of this string is `length + 1` bytes including the null terminator already present there. But in case of the formatting, the last byte - i.e, the null terminator is not considered. So only the bytes equivalent to their `strlen` is written. Yet there exists that **one** additional null terminator which is added by `snprintf/sprintf` itself. 

### Doubt 2 :

**What if we write not to NULL, but to existing buffer? What happens if we write zero bytes to any buffer? What about writing non zero bytes to existing buffer or NULL?**


**Answer : The four cases for `snprintf(s, n, fmt, ...)`**

**1. `n=0`, `s=NULL`**

This is the dry run case we used for getting the number of bytes we need to write for creating a malloc space. 

```c
int len = snprintf(NULL, 0, "hello %s", "world");
// len = 11, nothing written, so there is no UB
```

C11 explicitly carves out this case: *"if n is zero, nothing is written, and s may be a null pointer."* This is just a canonical idiom for *computing required buffer size*.

**2. `n=0`, `s=existing buffer`**

This is also well defined. If there is an existing buffer to which we can write to, we can write. No harm in that. But we write nothing to that buffer (that is 0 bytes.)

```c
char buf[32] = "existing";
snprintf(buf, 0, "hello");
// buf is still "existing" — not even a '\0' is written
```

Same rule applies here too. — n=0 means nothing is written, full stop. This surprises some friend of mine who expect at least a null terminator. Compare with n=1: (this is when null terminator is included.)

```c
snprintf(buf, 1, "hello");
// buf[0] = '\0' — empty string, everything else untouched
```


So `n=0` → untouched, `n=1` → silent truncation to empty string. That truncation. Truncation is different from overflow habibi.

**3. `n>0`, `s=NULL` - undefined behavior**

```c
snprintf(NULL, 5, "hello");  // UB
```

The standard's "s may be a null pointer" exemption only applies when n=0. Once n>0, the implementation must write at least a null terminator somewhere, and dereferencing NULL to do that is UB. In practice it segfaults, but you can't rely on that — it's just UB.

That is we may be writing in some forbidden address or something like that, which will imply `SIGSEGV`. Nice word. Is not it?

**4. `n>0`, `s=existing buffer`**

This is normal `snprintf` and totally permitted. 

```c
char buf[8];
snprintf(buf, 8, "hello %s", "world");
// buf = "hello w\0" — truncated to n-1 chars + '\0'
```

Always writes exactly one null terminator at position `min(actual_length, n-1)`. Return value is always the *would-be* length regardless of truncation, so `ret >= n` tells you truncation occurred.

**Conditions table**

| n | s | Result |
|---|---|---|
| 0 | NULL | Well-defined, dry run, returns would-be length |
| 0 | existing | Well-defined, buffer **completely untouched** |
| >0 | NULL | **UB** (segfault in practice) |
| >0 | existing | Normal write, always null-terminated, truncates if needed |

The asymmetry between `n=0,s=NULL` (ok) and `n>0,s=NULL` (UB) is the thing worth burning into memory — it's easy to assume NULL is always safe or always unsafe, and neither is right (this is what I learnt now.)

### This is the End of this Doubt Section.
Good Luck Understanding this.
