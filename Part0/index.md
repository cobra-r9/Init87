# PART 0 — Before You Write a Line

---

## Raw Index

0.1   What C is — compiled, statically typed, manual memory, close-to-metal
0.2   What C is not — no OOP, no GC, no bounds checking, no exceptions
0.3   History — Ritchie 1972, K&R, ANSI C89, C99, C11, C17, C23
0.4   Why learn C — everything else is built on it
0.5   C vs C++ — what they share, where they diverge
0.6   The compilation model — source → preprocessor → compiler → assembler → linker → binary
0.7   Toolchain — gcc, clang, as, ld, ar
0.8   Your first program — #include, main(), printf, return 0
0.9   Compiling — gcc file.c -o file, common flags (-Wall -Wextra -std=c11 -g -O2)
0.10  Running — ./file, exit codes
0.11  Errors vs warnings — what each means
0.12  The C standard library — what it is, what it isn't
0.13  Platform vs standard — what's portable, what's Linux/POSIX-only

---

## 0.1 What C Is

C is a **compiled, statically typed, manually managed, close-to-metal** language. Each of these words matters:

- **Compiled** — your source code is not interpreted line by line at runtime. It is translated entirely into machine code before it ever runs. The CPU executes your binary directly — there is no interpreter sitting in between.
- **Statically typed** — every variable has a type that is fixed at compile time. The compiler knows whether something is an `int` or a `char*` before the program runs. There is no runtime type discovery, no dynamic dispatch unless you build it yourself.
- **Manual memory** — there is no garbage collector. You decide when memory is allocated and when it is freed. If you forget to free it, it leaks. If you free it twice, it's undefined behavior. If you use it after freeing, it's undefined behavior. The machine does exactly what you tell it — no more, no less.
- **Close-to-metal** — C maps almost directly to what the hardware does. A pointer is a memory address. An array is a contiguous block of bytes. A function call is a `CALL` instruction. You are one thin layer above assembly. This is why operating systems, compilers, databases, and embedded firmware are written in C.

---

## 0.2 What C Is Not

Understanding what C deliberately lacks is as important as knowing what it has:

- **No OOP** — there are no classes, no inheritance, no method dispatch, no constructors or destructors. You have structs and functions. If you want object-like patterns, you build them manually with function pointers and discipline.
- **No garbage collector** — memory is not reclaimed automatically. Every `malloc` must have a matching `free`. The runtime does not watch your allocations. This gives you total control and total responsibility.
- **No bounds checking** — if you declare `int a[5]` and write to `a[9]`, the compiler doesn't stop you. The runtime doesn't stop you. You just wrote to memory you don't own. What happens next is undefined — silent corruption, crash, security hole.
- **No exceptions** — there is no `try/catch`. Errors are communicated through return values, the global `errno`, or output parameters. You must check every return value. If you don't, you will silently proceed with broken state.
- **No built-in strings** — there is no string type. A string is a null-terminated array of `char`. All string operations are manual or through library functions.
- **No modules (until C23, partially)** — code is organized through header files and translation units, a system from the 1970s with all its sharp edges.

C does not protect you from yourself. That is a design choice, not an oversight.

---

## 0.3 History

Knowing where C came from explains why it is the way it is:

- **1969–1972** — Dennis Ritchie at Bell Labs develops C to rewrite the Unix kernel, which was originally in assembly. C is born as a systems language for real work on real hardware.
- **1978** — Brian Kernighan and Dennis Ritchie publish *The C Programming Language*. This book is the de facto standard. The dialect it describes is called **K&R C**.
- **1989 — ANSI C / C89** — The American National Standards Institute standardizes C. This is the first official standard. Also called **C90** (ISO ratified it in 1990). This is the baseline. Anything written to C89 is maximally portable.
- **1999 — C99** — Major update. Adds `//` comments, `<stdint.h>`, `<stdbool.h>`, variable-length arrays, designated initializers, inline functions, mixed declarations and code, `restrict`, and more. Most compilers support this fully.
- **2011 — C11** — Adds `_Atomic`, `_Generic`, anonymous structs/unions, `_Static_assert`, threading support (`<threads.h>`), improved Unicode support. VLAs become optional. This is the most widely used modern standard.
- **2017 — C17** — A bug-fix release. No new features. Just clarifications and defect fixes to C11. Also called C18.
- **2023 — C23** — Adds `typeof`, `#embed`, `nullptr`, `[[attributes]]`, bit-precise integers, improved `constexpr`, and more. Compiler support is still rolling out.

When you write C today, you almost always target **C11** or **C99**. `gcc -std=c11` is the standard starting point.

---

## 0.4 Why Learn C

Not because it's pleasant. Because it's foundational:

- **The Linux kernel** is C. **CPython** (Python's runtime) is C. **SQLite**, **PostgreSQL**, **Redis**, **Nginx**, **OpenSSL**, **Git** — all C. The entire Unix/POSIX ecosystem is a C API.
- **Every language you use runs on C** (or something compiled through it). Python calls C extensions. Node.js is built on V8, which is C++. Your JVM is C++. Understanding C means understanding what those languages are actually doing.
- **Memory, pointers, the stack, the heap** — these concepts don't stop existing because you're writing Python. You just stop seeing them. Learning C makes them visible. You become a better programmer in every language.
- **Embedded and systems work** — microcontrollers, device drivers, operating systems, real-time systems — C is the language of that world and will remain so for decades.
- **Debugging** — when something crashes hard — a segfault, a corrupted heap, a memory leak — understanding C is what lets you read a core dump, interpret `valgrind` output, and understand what actually went wrong.

---

## 0.5 C vs C++

C++ is not "C with classes bolted on" — though it started that way. They share a common ancestor but are now distinct languages:

**What they share:**
- Basic syntax — `if`, `for`, `while`, operators, `printf`, pointers, arrays
- The C standard library (C++ includes it)
- Manual memory (though C++ adds RAII and smart pointers on top)
- The same compilation model — preprocessor, compiler, linker
- Most low-level behavior — pointer arithmetic, structs, function pointers

**Where they diverge:**
- C++ has classes, inheritance, virtual dispatch, templates, operator overloading, namespaces, references, exceptions, RAII, lambdas, the STL
- C++ has constructors and destructors — resource cleanup is automatic if you use RAII properly
- C++ is vastly more complex — its specification is thousands of pages; C's is hundreds
- C is a better language for **embedding, interoperability, and ABI stability** — `extern "C"` exists in C++ for a reason
- C is strict about certain things C++ is lenient about — e.g., implicit `void*` conversion
- Valid C is often not valid C++ — they are not the same language

Learn C first. It forces you to understand memory and control flow without abstraction layers in the way. C++ makes more sense after C.

---

## 0.6 The Compilation Model

This is the pipeline your source code travels through before it becomes a running program. Most people think of it as one step — it is four:

```
source.c
   ↓
[Preprocessor]     — cpp
   ↓
preprocessed .i
   ↓
[Compiler]         — cc1 (gcc's frontend)
   ↓
assembly .s
   ↓
[Assembler]        — as
   ↓
object file .o
   ↓
[Linker]           — ld
   ↓
executable binary
```

**Preprocessor (`cpp`):**
Runs before compilation. Handles all `#` directives: `#include` pastes in header files, `#define` substitutes macros, `#ifdef`/`#ifndef` conditionally includes or excludes code. The output is pure C — no `#` directives remain. You can see this output with `gcc -E file.c`.

**Compiler:**
Takes preprocessed C and produces assembly. This is where type checking, optimization, and code generation happen. You can stop here with `gcc -S file.c` and inspect the `.s` file.

**Assembler (`as`):**
Converts assembly into machine code, producing an **object file** (`.o`). The object file contains binary code but with unresolved references — calls to functions defined elsewhere are left as placeholders.

**Linker (`ld`):**
Takes one or more object files, resolves all symbol references between them, pulls in library code (like `printf` from `libc`), and produces the final executable. This is where "undefined reference to `foo`" errors come from — the linker can't find a symbol.

Understanding this pipeline is essential. Every confusing error — "implicit declaration of function", "undefined reference", "multiple definition" — makes sense once you know which stage it comes from.

---

## 0.7 Toolchain

The tools that execute the compilation pipeline:

**`gcc`** — GNU Compiler Collection. The default C compiler on Linux. Drives the entire pipeline — it calls the preprocessor, compiler, assembler, and linker for you. When you run `gcc file.c -o file`, that one command does all four stages.

**`clang`** — LLVM-based compiler. A modern alternative to gcc. Produces better error messages, is faster to compile, and is the default on macOS. On Linux, both are available. For learning, prefer clang for its error clarity.

**`as`** — the GNU assembler. Converts `.s` assembly files into `.o` object files. You rarely invoke this directly — gcc calls it internally.

**`ld`** — the GNU linker. Resolves symbols and produces executables or shared libraries. You almost never call this directly — gcc calls it with the right flags. When you do need to call it manually (rare), it's extremely verbose.

**`ar`** — the archiver. Creates static libraries (`.a` files), which are just archives of `.o` object files. Used as: `ar rcs libfoo.a foo.o bar.o`. The linker pulls object files out of `.a` archives as needed.

**Other tools you'll use constantly:**
- `make` — build automation, runs the right compile commands
- `gdb` — debugger
- `valgrind` — memory error detector
- `nm` — lists symbols in object files
- `objdump` — disassembles binaries
- `ldd` — shows shared library dependencies of an executable
- `strace` — traces system calls at runtime

---

## 0.8 Your First Program

Every part of this matters:

```c
#include <stdio.h>

int main(void) {
    printf("Hello, world\n");
    return 0;
}
```

**`#include <stdio.h>`**
This is a preprocessor directive. It pastes the contents of the `stdio.h` header file directly into your source. That header contains the *declaration* of `printf` — it tells the compiler that `printf` exists, what arguments it takes, and what it returns. Without this, the compiler doesn't know what `printf` is. The angle brackets `< >` mean "look in system include directories." Quotes `" "` mean "look relative to the current directory first."

**`int main(void)`**
`main` is the entry point. When the OS runs your program, execution starts here. `int` is the return type — `main` returns an integer (the exit code) to the OS. `void` in the parameter list means "this function takes no arguments." You can also write `int main(int argc, char *argv[])` to receive command-line arguments.

**`printf("Hello, world\n")`**
`printf` is defined in `<stdio.h>`. It writes formatted output to stdout. `\n` is the newline escape sequence. `printf` does not automatically add a newline — you must include it.

**`return 0`**
Returns exit code 0 to the OS. Zero means success by convention. Any nonzero value signals failure. The shell can inspect this with `echo $?` after your program runs.

---

## 0.9 Compiling

**Basic compilation:**
```bash
gcc file.c -o file
```

Compiles `file.c`, runs all four pipeline stages, outputs an executable named `file`.

**The flags you should always use:**

| Flag | Meaning |
|---|---|
| `-Wall` | Enable most important warnings |
| `-Wextra` | Enable additional warnings `-Wall` misses |
| `-std=c11` | Compile as C11. Be explicit — default varies by compiler version |
| `-g` | Include debug symbols (needed for gdb, valgrind) |
| `-O2` | Optimization level 2 — good for production builds |
| `-O0` | No optimization — best for debugging (code matches source) |
| `-Werror` | Treat warnings as errors — enforces clean code |
| `-pedantic` | Strictly enforce the standard, reject extensions |
| `-fsanitize=address,undefined` | Enable AddressSanitizer + UBSan — catches memory bugs at runtime |

**Your standard learning invocation:**

```bash
gcc -Wall -Wextra -std=c11 -g -fsanitize=address,undefined file.c -o file
```

Run with this every time during development. It catches an enormous range of bugs.

**Stopping at intermediate stages:**
```bash
gcc -E file.c          # Stop after preprocessing, print to stdout
gcc -S file.c          # Stop after compilation, produce file.s (assembly)
gcc -c file.c          # Stop after assembling, produce file.o (object file)
```

---

## 0.10 Running & Exit Codes

**Running your binary:**
```bash
./file
```
The `./` is required. Without it, the shell searches `PATH` for a program named `file`. With `./`, you're explicitly saying "run the file in the current directory."

**Exit codes:**
When a program finishes, it returns an integer to the OS. This is the value you `return` from `main`, or pass to `exit()`.

```bash
./file
echo $?         # Prints the exit code of the last command
```

| Exit code | Meaning |
|---|---|
| `0` | Success |
| `1` | General error (convention) |
| `2` | Misuse of shell builtins |
| `127` | Command not found |
| Any nonzero | Failure of some kind |

The C standard defines `EXIT_SUCCESS` (0) and `EXIT_FAILURE` (1) in `<stdlib.h>`.

When a program is killed by a signal (e.g., segfault), the shell reports the exit code as `128 + signal_number`. A segfault (signal 11) gives exit code 139. This is how you know a crash occurred vs. a clean error exit.

---

## 0.11 Errors vs Warnings

The compiler communicates two fundamentally different things:

**Errors:**
The compiler cannot produce valid output. Compilation stops (or no binary is emitted). Examples: syntax errors, type mismatches the compiler can't resolve, undeclared identifiers, missing return in non-void function. You must fix every error before you have a runnable program.

**Warnings:**
The code is syntactically valid and the compiler will produce output, but something looks suspicious. Examples: unused variable, implicit function declaration, signed/unsigned comparison, returning pointer to local variable, potentially uninitialized variable. Warnings are the compiler telling you "this will compile, but I think you made a mistake."

**Critical rule: treat every warning as an error.** A warning ignored is a bug deferred. Use `-Werror` to enforce this mechanically. The codebase discipline of zero warnings is what separates serious C from dangerous C.

**Common warning sources and what they mean:**

| Warning | Likely cause |
|---|---|
| `implicit declaration of function` | You called a function before declaring it, or forgot the `#include` |
| `unused variable` | You declared something you never used — dead code |
| `comparison between signed and unsigned` | Comparing `int` with `size_t` — dangerous, can produce wrong results |
| `control reaches end of non-void function` | A code path doesn't `return` a value |
| `format specifier mismatch` | `printf("%d", some_long)` — wrong type for format string |

---

## 0.12 The C Standard Library

The standard library is what C ships with — a set of functions and types every conforming C implementation must provide:

**What it is:**
A collection of headers and their associated functions, standardized by the C specification. When you `#include <stdio.h>` and call `printf`, you're using the standard library. It covers:
- I/O (`stdio.h`) — printf, scanf, fopen, fread, fwrite
- Memory (`stdlib.h`) — malloc, calloc, realloc, free
- Strings (`string.h`) — strlen, strcpy, memcpy, memset
- Math (`math.h`) — sin, cos, sqrt, pow
- Time (`time.h`) — time, clock, difftime
- Error handling (`errno.h`) — errno, strerror
- Type limits (`limits.h`, `float.h`) — INT_MAX, DBL_EPSILON
- Fixed-width types (`stdint.h`) — int32_t, uint64_t
- And more across ~30 headers

**What it is not:**
- It is not the OS. It does not directly make system calls (though it may internally)
- It has no networking, no threading (before C11), no filesystem operations beyond basic file I/O, no graphics, no IPC
- It is not the POSIX API — POSIX is a superset that adds `open()`, `read()`, `write()`, `socket()`, `fork()`, `pthread_*`, and hundreds more. POSIX is available on Linux/macOS but not part of the C standard.
- It is not big. Compared to Python's standard library or Java's, C's is minimal by design.

The standard library is implemented in `libc`. On Linux, this is almost universally **glibc** (GNU C Library). On embedded systems it might be **newlib** or **musl**. `libc` is automatically linked into every C program — you never need `-lc`.

---

## 0.13 Platform vs Standard — Portability

Not all C is equally portable. There are three distinct layers:

**1. ISO C Standard — fully portable:**
Anything defined in the C standard (the headers and functions in section 0.12) works on every conforming implementation — Linux, macOS, Windows, embedded targets, anything. Write to this layer for maximum portability.

**2. POSIX — portable to Unix-like systems:**
POSIX (Portable Operating System Interface) extends C with a Unix API. Functions like `open()`, `read()`, `write()`, `close()`, `fork()`, `exec()`, `socket()`, `pthread_create()`, `mmap()` are POSIX, not ISO C. They work on Linux and macOS. They do not exist on bare-metal embedded targets and are not natively available on Windows (though WSL and Cygwin provide them). Most serious C systems programming uses POSIX heavily.

**3. Platform-specific — not portable:**
Linux-specific syscalls (`epoll`, `io_uring`, `signalfd`, `eventfd`), glibc extensions, compiler-specific attributes (`__attribute__((packed))`), Windows API (`CreateFile`, `WaitForSingleObject`) — none of this is portable. You can use it, but you're tying yourself to a platform.

**The practical rule:**
- If it's in a `<header.h>` in the C standard — portable everywhere
- If it's documented in POSIX (man section 2 or 3) — portable to Linux/macOS
- If you're not sure — check `man 3 function_name` and look at the "Conforming To" section

For learning, you'll be on Linux. You will use POSIX constantly and eventually platform-specific Linux APIs. Just know which layer you're in.

---
