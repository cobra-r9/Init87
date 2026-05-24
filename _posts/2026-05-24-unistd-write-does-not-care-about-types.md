---
title: "Raw Bytes vs Text- Why Extensions Means Nothing to Unix"
description: "A doubt from the file I/O session : why does the file command call new_out.txt data but output.txt ASCII text, even though both share the same .txt extension?"
type: doubt
tags: [file-io, ieee754, magic-bytes, write-syscall]
---

Here is the exact doubt from the code :

```c
// but doubts! doubts :
// why did the file <filepath> command's output to file output.txt an ASCII text,
// but not the file new_out.txt a data type? Though both have a .txt file type?
```

And the output that triggered it :

```bash
file new_out.txt
# new_out.txt: data
```

Before getting into it, one question needs a clean answer first :
**What does the `file` command actually look at? The filename? The extension? The contents?**

> The answer to this single question resolves the entire doubt. And the answer will lead you somewhere important — right into IEEE 754, the format your CPU uses to store floating point numbers in memory and on disk.

## What Does the `.txt` Extension Mean to Unix?

Nothing. Absolutely nothing.

This is not an exaggeration. The kernel stores a filename as a plain string inside a directory entry — it is just a sequence of bytes that maps to an inode number. The kernel does not parse the extension, does not index it, and has no concept of "file type" encoded in the name. There is no field in the inode that says "this file contains text." The inode stores permissions, timestamps, size, and pointers to data blocks on disk. That is all it knows.

When you called `open("new_out.txt", O_WRONLY | O_CREAT | O_TRUNC, mode)`, the kernel looked at `"new_out.txt"` as a path to resolve — found or created the inode, handed you a file descriptor, and stepped away entirely. The `.txt` was irrelevant to every step of that process.

## So How Does `file` Actually Decide?

The `file` command uses a mechanism called **magic bytes**. It maintains a database of known byte patterns at known offsets inside files. For example :

```
offset 0 → bytes 89 50 4E 47  →  PNG image
offset 0 → bytes FF D8 FF      →  JPEG image
offset 0 → bytes 7F 45 4C 46  →  ELF executable
offset 0 → bytes 25 50 44 46  →  PDF document
```

It reads the file's raw bytes and tries to match them against this database. If nothing matches, it falls back to a simpler heuristic : it scans the first few kilobytes and checks whether every byte falls inside the **printable ASCII range** (values 32 through 126, plus common control characters like `\n` = 10 and `\t` = 9). If all bytes pass that check — "ASCII text". If even one byte falls outside that range — "data". The word "data" is just `file`'s way of saying : *I have no idea what this is.*

## Why Did output.txt Pass?

Because you wrote the string `"hello world!\n"`, which is 13 bytes, every single one of them a clean printable ASCII character. You can see this directly :

```bash
xxd output.txt
# 00000000: 6865 6c6c 6f20 776f 726c 6421 0a       hello world!.
```

`68` is `'h'`, `65` is `'e'`, right through to `0a` which is `'\n'` — a recognized control character. Every byte is in range. `file` scans them, sees nothing suspicious, and calls it ASCII text.

## Why Did new_out.txt Fail?

Because you wrote a `Coordinates` struct — and a struct is not text. It is raw memory, copied verbatim to disk by `write()`. Your struct held three `float` values, and floats are stored in memory using **IEEE 754 single precision** — a binary format that has nothing to do with human-readable characters.

Take `8.4f` as a concrete example. In IEEE 754 single precision, `8.4` is represented in 32 bits like this :

```
Sign   Exponent    Mantissa
  0   10000010   00001100110011001100110
```

Which in hexadecimal is `0x4106_6666`, and on your x86 machine (which is little-endian), the bytes are laid out in reverse order on disk :

```
66 66 06 41
```

The byte `0x06` is the problem. That is the ASCII control character **ACK** (Acknowledge) — value 6, well outside the printable range of 32–126. The moment `file` encounters it, the ASCII heuristic fails and the file is classified as "data."

You can verify all of this directly :

```bash
xxd new_out.txt
# 00000000: 6666 0641 cdcc 4b41 9a99 9941            ff.A..KA...A
```

Those 12 bytes are the exact IEEE 754 binary representations of `8.4f`, `12.7f`, and `19.2f` — the same bytes that were sitting in the `Coordinates` struct in your process's memory, now living on disk. `write()` copied them without touching a single bit.

## The Root Cause : `write()` is Completely Type-Blind

This is the most important thing to internalize from this session. `write()` has the following signature :

```c
ssize_t write(int fd, const void *buf, size_t count);
```

The second argument is `const void *` — a raw pointer to memory with no type information whatsoever. The kernel does not know or care whether those bytes represent a string, a struct, an integer, or random noise. It takes exactly `count` bytes starting at `buf` and copies them into the file. No interpretation, no conversion, no null terminator handling. Pure bytes.

When you wrote the string :

```c
file_write_wct("output.txt", "hello world!\n", 13, 0664);
```

The bytes that went to disk happened to be ASCII — not because `write()` did anything special for strings, but because ASCII characters are just bytes in the range 32–126, and that is what the string literal contains in memory.

When you wrote the struct :

```c
file_write_wct("new_out.txt", (const void *)&coor, size_coor, 0664);
```

The bytes that went to disk were IEEE 754 binary floats — not because `write()` did anything special for structs, but because that is how your CPU represents floats in memory, and `write()` copied them exactly as-is.

## Is There a Way to Write Floats as Human-Readable Text?

Absolutely. You would use `dprintf()` — which is `printf()` but targeting a file descriptor instead of stdout :

```c
dprintf(fd, "x : %f\ny : %f\nz : %f\n", coor.x, coor.y, coor.z);
```

This converts the binary float representation into a decimal ASCII string before writing — the same conversion that `printf()` does when printing to your terminal. The resulting file would contain something like `x : 8.400000\n` as actual ASCII characters, and `file` would call it "ASCII text."

The tradeoff is that the file becomes larger and human-readable, but you lose precision and you can no longer `read()` the bytes straight back into a `float` variable without parsing. For binary data that programs need to read back efficiently, raw binary (what you did) is the correct approach. For data that humans need to read or inspect, text conversion is the right call. Knowing which to choose — and why — is the essence of understanding I/O at this level.

<gh-include src="cobra-r9/Init87/main/misc/files/exp2/open-writev1.c"></gh-include>

### This is the End of this Doubts Section.
Good Luck Understanding this. Here is the original code for what I have done. 


