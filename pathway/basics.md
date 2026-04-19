# Basics


# C Programming — Master Index (Before File I/O)

Everything you must know before touching a file descriptor. Ordered from absolute zero to the threshold of systems programming.


## PART 0 — Before You Write a Line

```
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
```



## PART 1 — Fundamental Types

```
1.1   Integer types — char, short, int, long, long long
1.2   Unsigned variants — unsigned char, unsigned int, etc.
1.3   Sizes are not guaranteed — sizeof, <limits.h>, INT_MAX, CHAR_BIT
1.4   Fixed-width types — int8_t, uint32_t, int64_t (stdint.h)
1.5   Least/fast types — int_least32_t, int_fast32_t (stdint.h)
1.6   intptr_t / uintptr_t / ptrdiff_t / size_t / ssize_t
1.7   Floating point — float, double, long double
1.8   IEEE 754 — representation, NaN, Inf, -0, precision limits
1.9   <float.h> — FLT_MAX, DBL_EPSILON, etc.
1.10  char — signed vs unsigned (implementation-defined), use cases
1.11  _Bool / bool — stdbool.h, true, false
1.12  void — incomplete type, void*, function returns
1.13  Type qualifiers — const, volatile, restrict, _Atomic
1.14  const — what it means, what it doesn't, const-correctness
1.15  volatile — when to use (hardware registers, signal handlers)
1.16  restrict — pointer aliasing hint, what it promises the compiler
1.17  Literals — integer (0x, 0b, 0, u, l, ul, ll), float (f, l), char ('\n', '\0', '\x41')
1.18  String literals — "hello", stored where, NUL terminator, immutable
1.19  Compound literals — (int[]){1,2,3}, (struct Point){.x=1}
```



## PART 2 — Variables, Scope & Storage

```
2.1   Declaration vs definition — what each means, where each goes
2.2   Initialization — default values (none for locals), zero for globals
2.3   Scope — block, function, file (translation unit)
2.4   Linkage — none, internal (static), external
2.5   Storage duration — automatic, static, allocated, thread-local
2.6   Storage class specifiers — auto, register, static, extern
2.7   static (local) — persists across calls, initialized once
2.8   static (global/function) — internal linkage, not visible outside TU
2.9   extern — declaration without definition, referencing other TUs
2.10  register — hint only, modern compilers ignore it
2.11  _Thread_local — thread-local storage (C11)
2.12  The stack — where automatic variables live, frame layout
2.13  Stack overflow — recursion, large locals, VLAs
2.14  Global/static memory — BSS (zero-init) vs data (init) segments
2.15  Shadowing — inner scope hiding outer variable, compiler warnings
2.16  Tentative definitions — C's quirky external definition rules
```



## PART 3 — Operators

```
3.1   Arithmetic — +, -, *, /, % and their rules
3.2   Integer division — truncation toward zero
3.3   Modulo with negatives — implementation-defined in C89, defined in C99
3.4   Assignment — =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
3.5   Comparison — ==, !=, <, >, <=, >= (return int 0 or 1)
3.6   Logical — && (short-circuit), || (short-circuit), !
3.7   Bitwise — &, |, ^, ~, <<, >>
3.8   Left/right shift — behavior on signed vs unsigned, shift >= width UB
3.9   Bitwise idioms — set bit, clear bit, toggle bit, test bit, masks
3.10  Increment/decrement — ++i vs i++, prefix vs postfix semantics
3.11  Ternary — condition ? a : b
3.12  Comma operator — evaluates both, returns right (rare, used in for loops)
3.13  sizeof operator — compile-time, operand not evaluated
3.14  _Alignof operator — alignment of a type (C11)
3.15  Address-of — &var, gives pointer to var
3.16  Dereference — *ptr, accesses value at pointer
3.17  Member access — . (direct), -> (via pointer)
3.18  Array subscript — a[i] is exactly *(a+i)
3.19  Cast — (type)expr, explicit conversion
3.20  Operator precedence — full table, common mistakes (& vs ==, * vs +)
3.21  Associativity — left vs right, assignment is right-associative
3.22  Sequence points — when side effects are guaranteed to complete
3.23  Evaluation order — largely unspecified, i++ + i++ is UB
```



## PART 4 — Control Flow

```
4.1   if / else if / else — syntax, dangling else problem
4.2   switch / case / default — fall-through, break, char/int only
4.3   switch fall-through — intentional vs accidental, __attribute__((fallthrough))
4.4   while loop — condition checked first
4.5   do-while loop — body executes at least once
4.6   for loop — init; condition; increment, all parts optional
4.7   break — exits innermost loop or switch
4.8   continue — skips to next iteration
4.9   goto — jumps to label, forward and backward
4.10  goto for cleanup — the legitimate C idiom (error handling)
4.11  return — exits function, optional value
4.12  Infinite loops — for(;;), while(1), intentional uses
4.13  Loop invariants — what must be true on every iteration
4.14  Nested loops and labeled break (C has none — goto workaround)
4.15  Early exit patterns — guard clauses vs nested ifs
```



## PART 5 — Functions

```
5.1   Function definition — return type, name, params, body
5.2   Function declaration (prototype) — why required before use
5.3   Return values — return stmt, implicit return (UB in non-void)
5.4   void functions — no return value
5.5   Parameters vs arguments — definition vs call
5.6   Pass by value — C always copies, no references
5.7   Passing arrays — decays to pointer, size not carried
5.8   Passing structs — copied by value (expensive for large structs)
5.9   Passing pointers — simulating pass-by-reference
5.10  const pointers — const T*, T* const, const T* const
5.11  Variadic functions — ..., va_list, va_start, va_arg, va_end (<stdarg.h>)
5.12  Implementing printf-like functions — format string dispatch
5.13  Recursion — base case, recursive case, stack depth
5.14  Tail recursion — what it is, C compilers and TCO
5.15  Function pointers — declaration, assignment, calling, typedef
5.16  Arrays of function pointers — dispatch tables, vtable simulation
5.17  Callbacks — passing function pointers as arguments
5.18  inline functions — hint only, use for small hot functions
5.19  static inline — the standard header-only function pattern
5.20  noreturn — _Noreturn / [[noreturn]] (C23), abort(), exit()
5.21  main() — argc, argv, envp, return value conventions
5.22  Calling conventions — how arguments are passed at ABI level (x86-64 SysV)
5.23  Stack frames — what the compiler puts on the stack per call
5.24  The call stack — growing downward, frame pointer, return address
```



## PART 6 — Arrays

```
6.1   Array declaration — T name[N], N must be compile-time constant (C89/C11)
6.2   Array initialization — {1,2,3}, partial init zeros rest, {0} to zero all
6.3   Array access — name[i], zero-indexed, no bounds checking
6.4   Array size — sizeof(arr)/sizeof(arr[0]), only works on arrays not pointers
6.5   Array decay — arr used in expression becomes &arr[0] (pointer)
6.6   What doesn't decay — sizeof, &arr, function argument declared as array
6.7   Passing arrays to functions — always a pointer, size lost
6.8   Returning arrays — impossible directly, use pointer or struct
6.9   Multidimensional arrays — T name[R][C], row-major layout
6.10  Multidimensional array passing — only first dim can be omitted
6.11  Variable-length arrays (VLA) — C99, size at runtime, stack allocated
6.12  VLA dangers — stack overflow, C11 makes optional, avoid in practice
6.13  Array of pointers vs 2D array — different memory layouts
6.14  const arrays — const int a[] = {1,2,3}
6.15  Flexible array members — struct with T arr[] at end (C99)
6.16  Designated initializers — {[2]=5, [0]=1} (C99)
```



## PART 7 — Strings

```
7.1   C strings — null-terminated char array, no string type
7.2   String literals — "hello" → {'h','e','l','l','o','\0'}
7.3   String literal storage — read-only, modifying is UB
7.4   char[] vs char* — mutable array vs pointer to literal
7.5   strlen() — counts without null, O(n)
7.6   strcpy() / strncpy() — copy, strncpy pitfalls (no null if truncated)
7.7   strcat() / strncat() — concatenation, buffer overflow risk
7.8   strcmp() / strncmp() — lexicographic comparison, return value meaning
7.9   strchr() / strrchr() — finding a character
7.10  strstr() — finding a substring
7.11  strtok() / strtok_r() — tokenizing, destructive, strtok not thread-safe
7.12  strsep() — GNU alternative to strtok
7.13  memcpy() / memmove() — block copy, memmove handles overlap
7.14  memset() — filling memory with a byte value
7.15  memcmp() — comparing raw memory blocks
7.16  memchr() — finding a byte in a block
7.17  sprintf() / snprintf() — formatting into a buffer
7.18  atoi() / atol() / atof() — string to number (no error detection, avoid)
7.19  strtol() / strtoul() / strtod() — safe string to number with error detection
7.20  Safe string handling patterns — always size-bound, always check
7.21  Buffer overflow — the classic C security bug, stack smashing
7.22  strdup() / strndup() — POSIX, allocates and copies a string
7.23  <ctype.h> — isalpha, isdigit, isspace, toupper, tolower, etc.
7.24  Wide strings — wchar_t, wcslen, wcscpy (<wchar.h>)
7.25  Multibyte strings — UTF-8 in C, mbstowcs, locale-dependent functions
```



## PART 8 — Pointers (The Core of C)

```
8.1   What a pointer is — an address, nothing more
8.2   Pointer declaration — T *p, reading right-to-left
8.3   & and * — address-of and dereference
8.4   NULL — the null pointer, always check before deref
8.5   Pointer to pointer — T **pp, chaining
8.6   Pointer arithmetic — p+n advances by n*sizeof(T)
8.7   Pointer difference — ptrdiff_t, only valid within same array
8.8   Pointer comparison — only valid within same array + one past end
8.9   Array/pointer duality — a[i] == *(a+i) == *(i+a) == i[a]
8.10  Pointer to array — T (*p)[N], distinct from T *p
8.11  Pointers to functions — T (*f)(args), typedef cleanup
8.12  void* — generic pointer, no arithmetic (GCC extension allows it)
8.13  Implicit void* conversion — malloc returns void*, no cast needed in C
8.14  const correctness with pointers — 4 combinations explained
8.15  Pointer aliasing — two pointers to same memory, restrict keyword
8.16  Strict aliasing rule — accessing object via wrong type pointer is UB
8.17  Type punning safely — memcpy, union (C99+), not cast
8.18  Dangling pointers — pointing to freed/stack memory, use-after-free
8.19  Wild pointers — uninitialized pointer, immediate UB on deref
8.20  Double free — freeing same pointer twice, heap corruption
8.21  One-past-end pointer — valid to form, invalid to dereference
8.22  Pointer to struct member — offsetof(), padding implications
8.23  Opaque pointers — hiding struct internals via forward declaration
8.24  Pointer-sized integers — intptr_t, uintptr_t, casting rules
8.25  Near/far pointers — historical segmented memory (8086), irrelevant now
8.26  Interior pointers — pointing into the middle of an allocation
```



## PART 9 — Memory Management

```
9.1   The memory map — text, data, BSS, heap, stack, mmap regions
9.2   Stack allocation — automatic, LIFO, no free required, limited size
9.3   Heap allocation — manual, dynamic size, must free
9.4   malloc() — allocates n bytes, uninitialized, returns NULL on failure
9.5   calloc() — allocates n*size bytes, zero-initialized
9.6   realloc() — resize allocation, may move pointer
9.7   free() — releases heap memory, pointer becomes dangling
9.8   Always check malloc return — NULL means out of memory
9.9   Memory leak — allocated but never freed, accumulates
9.10  Use-after-free — accessing freed memory, UB, security bug
9.11  Heap corruption — writing past allocation boundary, clobbers metadata
9.12  The allocator — glibc malloc internals (bins, chunks, arcs)
9.13  alloca() — stack allocation (non-standard, dangerous, avoid)
9.14  Aligned allocation — posix_memalign(), aligned_alloc() (C11)
9.15  Custom allocators — arena/pool/slab, why to build your own
9.16  Arena allocator — bump pointer, free all at once
9.17  Pool allocator — fixed-size objects, O(1) alloc/free
9.18  Memory ownership — who allocates, who frees, single-ownership rule
9.19  RAII-style in C — cleanup with goto, GCC __attribute__((cleanup))
9.20  valgrind — detecting leaks, use-after-free, invalid reads
9.21  AddressSanitizer (ASan) — compile-time instrumentation (-fsanitize=address)
9.22  MemorySanitizer (MSan) — uninitialized reads (-fsanitize=memory)
9.23  UBSan — undefined behavior detection (-fsanitize=undefined)
9.24  Electric Fence / DUMA — page-protected heap debugging
```



## PART 10 — Structs, Unions & Enums

```
10.1  struct — grouping heterogeneous data, definition, declaration
10.2  struct initialization — {val1, val2}, designated {.field=val} (C99)
10.3  Member access — . (direct), -> (via pointer)
10.4  Struct padding & alignment — compiler inserts gaps, sizeof surprises
10.5  __attribute__((packed)) — eliminating padding, performance tradeoff
10.6  offsetof() — byte offset of a member (<stddef.h>)
10.7  Struct assignment — copies all members (including padding)
10.8  Passing structs — by value (copy), by pointer (reference)
10.9  Returning structs from functions — copy out, RVO optimization
10.10 Forward declaration — struct Foo; before full definition
10.11 Self-referential structs — linked list node, tree node
10.12 Opaque struct pattern — typedef + forward decl in header, define in .c
10.13 Intrusive data structures — embedding list node in struct (container_of)
10.14 container_of macro — deriving outer struct from inner member pointer
10.15 Nested structs — struct inside struct
10.16 Anonymous structs/unions — C11, members promoted to enclosing scope
10.17 Bit fields — unsigned int x:3, packing flags, portability issues
10.18 union — overlapping memory, only one member valid at a time
10.19 union use cases — type punning (carefully), variant types, protocol parsing
10.20 Tagged union pattern — struct with enum tag + union payload
10.21 enum — named integer constants
10.22 enum underlying type — int by default, not strongly typed
10.23 enum as bit flags — powers of two, combining with |
10.24 typedef — creating type aliases, struct/union/enum cleanup
10.25 typedef vs #define — type vs text substitution
```



## PART 11 — The Preprocessor

```
11.1  What the preprocessor does — text substitution before compilation
11.2  #include — file inclusion, <> vs "", include search paths
11.3  #include guards — #ifndef HEADER_H, #pragma once
11.4  #define — object-like macros, function-like macros
11.5  Macro pitfalls — operator precedence, double evaluation, no type safety
11.6  Safe macro patterns — wrap in do{}while(0), parenthesize everything
11.7  Variadic macros — __VA_ARGS__ (C99)
11.8  Stringification — #arg turns argument to string literal
11.9  Token pasting — a##b concatenates tokens
11.10 #undef — removing a macro definition
11.11 #if / #elif / #else / #endif — conditional compilation
11.12 #ifdef / #ifndef — defined/not-defined conditionals
11.13 defined() operator — #if defined(FOO) && defined(BAR)
11.14 Predefined macros — __FILE__, __LINE__, __func__, __DATE__, __TIME__
11.15 __STDC_VERSION__ — detecting C standard version
11.16 Feature test macros — _POSIX_C_SOURCE, _GNU_SOURCE, _XOPEN_SOURCE
11.17 #pragma — implementation-defined directives
11.18 #pragma once — non-standard but universally supported include guard
11.19 #error / #warning — compile-time error/warning messages
11.20 X-macros — table-driven code generation pattern
11.21 Macro metaprogramming — FOREACH, CONCAT, NARGS tricks
11.22 assert() — debug assertion, NDEBUG disables it
11.23 static_assert — _Static_assert(cond, msg) (C11), compile-time check
```



## PART 12 — Type System Deep Dive

```
12.1  Implicit conversions — integer promotion, usual arithmetic conversions
12.2  Integer promotion — char/short promoted to int in expressions
12.3  Usual arithmetic conversions — balancing types in binary ops
12.4  Signed/unsigned mixing — unsigned wins, sign extension pitfalls
12.5  Explicit cast — (type)expr, when required vs when a smell
12.6  Integer overflow — signed overflow is UB, unsigned wraps (defined)
12.7  Signed overflow UB — compiler assumes it never happens, optimization danger
12.8  Detecting overflow safely — __builtin_add_overflow, CERT rules
12.9  Conversion rank — bool < char < short < int < long < long long
12.10 Truncation — assigning larger type to smaller, defined for unsigned
12.11 Float-to-int conversion — truncation toward zero, UB if out of range
12.12 Pointer conversions — NULL, void*, function pointers
12.13 Strict aliasing in depth — what types may alias what
12.14 Effective type rule — what type an object actually has
12.15 lvalue vs rvalue — what can appear left/right of assignment
12.16 Type compatibility — when two struct types are the same
12.17 Incomplete types — array of unknown size, forward-declared struct
```



## PART 13 — Undefined Behavior (Critical)

```
13.1  What UB is — behavior the standard places no requirements on
13.2  Why UB exists — enables compiler optimizations
13.3  What compilers do with UB — assume it never happens, optimize around it
13.4  The UB minefield — list of common UB cases
13.5  Signed integer overflow — UB, compiler may delete overflow checks
13.6  Dereferencing NULL — always UB, always segfaults in practice
13.7  Out-of-bounds array access — UB even if the memory is mapped
13.8  Use-after-free — UB, can cause silent data corruption
13.9  Reading uninitialized variables — UB, value is not "random"
13.10 Modifying string literals — UB (segfault or silent corruption)
13.11 Strict aliasing violations — float* accessing int storage
13.12 Data races (without _Atomic) — UB in multithreaded code
13.13 Shifting by negative or >= width — UB
13.14 Signed integer overflow in loops — compiler may infinite-loop
13.15 Returning from non-void function without return — UB
13.16 Sequence point violations — i++ + i++ is UB
13.17 VLA size ≤ 0 — UB
13.18 Implementation-defined vs unspecified vs UB — the three categories
13.19 UBSan in practice — catching UB at runtime with -fsanitize=undefined
13.20 Nasal demons — why "it works on my machine" is meaningless with UB
```



## PART 14 — The C Standard Library

### `<stdlib.h>`
```
14.1  malloc/calloc/realloc/free — memory allocation
14.2  abort() / exit() / _Exit() / atexit() — process termination
14.3  getenv() / putenv() / setenv() — environment variables
14.4  system() — running shell commands (dangerous)
14.5  atoi/atol/atof vs strtol/strtod — safe conversions
14.6  qsort() — generic sort, comparator function pointer
14.7  bsearch() — binary search on sorted array
14.8  rand() / srand() — bad RNG, use arc4random or getrandom instead
14.9  abs() / labs() / llabs() — absolute value
14.10 div() / ldiv() — quotient and remainder together
14.11 EXIT_SUCCESS / EXIT_FAILURE — portable return codes
```

### `<string.h>`
```
14.12 Full function list — already covered in Part 7
14.13 memset/memcpy/memmove/memcmp/memchr
```

### `<math.h>`
```
14.14 Basic — sqrt, pow, fabs, ceil, floor, round, fmod
14.15 Trig — sin, cos, tan, asin, acos, atan, atan2
14.16 Exponential — exp, log, log2, log10
14.17 Hyperbolic — sinh, cosh, tanh
14.18 Error detection — errno, EDOM, ERANGE, fpclassify, isnan, isinf
14.19 Link with -lm
```

### `<stdio.h>` (non-file parts)
```
14.20 printf/fprintf/sprintf/snprintf/vprintf family
14.21 scanf/fscanf/sscanf family
14.22 puts/gets (never use gets)/putchar/getchar
14.23 perror() — printing errno string
```

### `<time.h>`
```
14.24 time_t / struct tm — time representations
14.25 time() — current Unix timestamp
14.26 clock() — CPU time used, CLOCKS_PER_SEC
14.27 difftime() — difference between two time_t
14.28 mktime() / gmtime() / localtime() — conversions
14.29 strftime() — formatting time to string
14.30 clock_gettime() — POSIX, nanosecond precision, CLOCK_MONOTONIC
```

### `<ctype.h>`
```
14.31 isalpha, isdigit, isalnum, isspace, ispunct, isprint, iscntrl
14.32 toupper, tolower — locale-dependent, use with unsigned char
```

### `<limits.h>` & `<float.h>`
```
14.33 CHAR_BIT, CHAR_MIN, CHAR_MAX, INT_MIN, INT_MAX, LLONG_MAX, etc.
14.34 FLT_MAX, DBL_EPSILON, LDBL_DIG, etc.
```

### `<stddef.h>`
```
14.35 NULL, size_t, ptrdiff_t, offsetof, max_align_t
```

### `<stdint.h>` & `<inttypes.h>`
```
14.36 Fixed-width types, PRId32/SCNu64 format macros for scanf/printf
```

### `<errno.h>`
```
14.37 errno, EINVAL, ENOMEM, ENOENT, EACCES, EBADF, common codes
```

### `<setjmp.h>`
```
14.38 setjmp() / longjmp() — non-local goto, exception simulation
14.39 When to use / not use, stack frame dangers
```

### `<signal.h>`
```
14.40 signal() — registering signal handlers (unreliable, use sigaction)
14.41 raise() — sending a signal to yourself
14.42 Common signals — SIGINT, SIGSEGV, SIGTERM, SIGKILL, SIGPIPE, SIGUSR1/2
14.43 Async-signal-safe functions — the short list of what's safe in handlers
```

### `<stdarg.h>`
```
14.44 va_list, va_start, va_arg, va_end, va_copy — variadic function support
```

### `<stdalign.h>` / `<stdnoreturn.h>` / `<stdbool.h>` (C11)
```
14.45 alignas, alignof, bool, true, false, noreturn
```

### `<threads.h>` & `<stdatomic.h>` (C11)
```
14.46 thrd_create/join/detach, mtx_*, cnd_* — C11 threads
14.47 _Atomic, atomic_store/load/fetch_add, memory_order_*
14.48 atomic_flag — the simplest atomic, spinlock use case
```



## PART 15 — Compilation, Linking & Build

```
15.1  Compilation units — one .c file = one translation unit
15.2  Header files — declarations, not definitions (mostly)
15.3  Header-only libraries — when and why
15.4  Static libraries — .a files, ar tool, linking order matters
15.5  Shared libraries — .so files, dynamic linking, -shared -fPIC
15.6  Symbol visibility — static, extern, __attribute__((visibility))
15.7  The linker — resolves symbols, common errors (undefined, multiply defined)
15.8  Link order — right-to-left, library dependency ordering
15.9  gcc flags — -I (include path), -L (lib path), -l (link library)
15.10 Optimization levels — -O0, -O1, -O2, -O3, -Os, -Og
15.11 Debug info — -g, -g3, DWARF format
15.12 Sanitizers — -fsanitize=address,undefined,memory,thread
15.13 Warnings — -Wall, -Wextra, -Wpedantic, -Werror, specific -W flags
15.14 Preprocessor flags — -D, -U, -E (stop after preprocessing)
15.15 Makefile basics — targets, prerequisites, recipes, variables, phony
15.16 make — implicit rules, pattern rules, automatic variables ($@, $<, $^)
15.17 pkg-config — getting cflags and libs for installed libraries
15.18 cmake basics — CMakeLists.txt, add_executable, target_link_libraries
15.19 nm — listing symbols in an object file
15.20 objdump — disassembly, section headers
15.21 ldd — listing shared library dependencies
15.22 readelf — ELF file inspection
15.23 strip — removing debug symbols from binary
15.24 ELF format — sections (.text, .data, .bss, .rodata), segments
```



## PART 16 — Debugging

```
16.1  gdb basics — run, break, next, step, continue, print, backtrace
16.2  gdb watchpoints — break on memory change
16.3  gdb core dumps — analyzing a crash post-mortem
16.4  gdb TUI — text user interface mode
16.5  printf debugging — the universal fallback
16.6  assert() — catching invariant violations early
16.7  valgrind memcheck — invalid reads, invalid frees, leaks
16.8  valgrind callgrind — profiling call graph
16.9  valgrind cachegrind — cache performance
16.10 AddressSanitizer output — reading leak/error reports
16.11 strace — tracing system calls
16.12 ltrace — tracing library calls
16.13 perf — CPU performance counters
16.14 gprof — sampling profiler
16.15 /proc/<pid>/maps — memory layout of running process
16.16 core_pattern — configuring core dump location
16.17 Debugging without a debugger — logging, bisection, rubber duck
```



## PART 17 — C Patterns & Idioms

```
17.1  Error return convention — return 0 on success, -1/errno on failure
17.2  Output parameters — passing pointer to write result into
17.3  goto cleanup — single-exit resource cleanup pattern
17.4  Boolean return — 0=false, nonzero=true (or inverted for errno style)
17.5  Opaque handle pattern — typedef void* Handle; hiding implementation
17.6  vtable in C — function pointer struct simulating polymorphism
17.7  Callback + context — void* userdata parameter
17.8  Builder pattern — init function + setters + build function
17.9  Iterator pattern — state struct + next() function
17.10 Defensive programming — validate all inputs, all pointers, all sizes
17.11 Const-correctness discipline — propagate const as far as possible
17.12 Null-safety discipline — check every pointer before deref
17.13 Ownership documentation — comment who owns each allocation
17.14 Header guards discipline — always, no exceptions
17.15 Minimal headers — include only what you need, forward-declare rest
17.16 POSIX-safe printf — %zu for size_t, %td for ptrdiff_t, PRId64 for int64_t
17.17 Safe integer arithmetic — checked math, saturation arithmetic
17.18 Compile-time assertions — _Static_assert for struct sizes, enum counts
17.19 X-macro dispatch tables — no-duplication enum + string + handler
```



## PART 18 — C Memory Model & Concurrency Basics

```
18.1  Sequential consistency — what programs assume, what CPUs do
18.2  Memory reordering — CPU and compiler both reorder
18.3  Volatile is not enough for threading — common misconception
18.4  _Atomic — C11 atomic types, guaranteed atomic read-modify-write
18.5  memory_order — relaxed, acquire, release, acq_rel, seq_cst
18.6  Acquire/release semantics — synchronizes-with relationship
18.7  atomic_flag — spinlock building block
18.8  Compare-and-swap — atomic_compare_exchange_strong/weak
18.9  Lock-free programming — when it helps, when it's wrong
18.10 Data races — two concurrent unsynchronized accesses = UB
18.11 pthreads — POSIX threads (separate deep topic, just awareness here)
18.12 When you need locking — shared mutable state between threads
```



## Now You're Ready for File I/O

At this point you understand:
- How memory works and who owns what
- Pointers well enough to not fear `FILE*` or raw `fd`
- The error handling conventions C uses (`errno`, return codes)
- The type system well enough to read any POSIX signature
- The preprocessor well enough to read any system header
- The standard library so you know what's already there

**→ File manipulation index (the one already provided) starts here.**



Total: **~350 topics across 18 parts** before a single file is opened.

Which part do you want to start with?
