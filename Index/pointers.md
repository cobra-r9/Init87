Now I have everything. Here's the complete master index.

---

# C Pointers & Memory — Complete Master Index

Everything from the hardware up to the most advanced pointer techniques in C.

---

## TIER 0 — The Hardware Foundation (What Memory Actually Is)

```
0.1   What RAM is — volatile storage, addressable bytes, physical addresses
0.2   The CPU and memory bus — how the CPU reads/writes RAM
0.3   Registers — the fastest storage, no address, CPU-local
0.4   The memory hierarchy — registers → L1 → L2 → L3 → RAM → disk
0.5   Cache lines — 64 bytes, what gets loaded on a read miss
0.6   Cache coherency — what happens when multiple cores read/write
0.7   Word size — 32-bit vs 64-bit, size of a pointer
0.8   Byte addressability — every byte has an address, not every bit
0.9   Endianness — little-endian vs big-endian, byte order in memory
0.10  Big-endian vs little-endian — which end of a multi-byte integer is stored first
0.11  x86-64 address space — 48-bit virtual, 64-bit pointer width
0.12  Physical address space — limited by RAM, managed by OS
0.13  Memory-mapped I/O — devices appear as memory addresses
```

---

## TIER 1 — Virtual Memory (The OS Abstraction)

```
1.1   What virtual memory is — each process sees its own private address space
1.2   Why virtual memory exists — isolation, protection, overcommit
1.3   Virtual address vs physical address — the mapping the kernel manages
1.4   Pages — fixed-size chunks (4KB typical), unit of mapping
1.5   Page frames — physical memory divided into same-size frames
1.6   Page table — kernel data structure mapping virtual pages → physical frames
1.7   Multi-level page tables — 4-level on x86-64 (PGD→PUD→PMD→PTE)
1.8   Page table entries (PTE) — frame number + permission bits + present bit
1.9   MMU — Memory Management Unit, hardware that does address translation
1.10  TLB — Translation Lookaside Buffer, hardware cache of recent translations
1.11  TLB miss — page table walk, expensive, why locality matters
1.12  TLB flush — on context switch, why process switches are costly
1.13  Page fault — accessing unmapped/not-present page, kernel handles it
1.14  Minor page fault — page exists but not mapped yet (demand paging)
1.15  Major page fault — page must be fetched from disk (swap)
1.16  Segmentation fault — accessing page with wrong permissions or unmapped
1.17  SIGSEGV — signal delivered on segfault, usually kills process
1.18  Demand paging — pages only loaded when first accessed
1.19  Copy-on-write (COW) — fork shares pages until one writes
1.20  Memory overcommit — kernel promises more than physical RAM exists
1.21  OOM killer — kernel kills processes when physical RAM exhausted
1.22  Swap space — disk used to page out cold pages
1.23  Huge pages — 2MB/1GB pages, fewer TLB entries needed
1.24  ASLR — Address Space Layout Randomization, security feature
1.25  Canonical addresses — on x86-64, bits 48-63 must sign-extend bit 47
```

---

## TIER 2 — Process Address Space Layout

```
2.1   The virtual address space — what a process "sees"
2.2   Address space diagram — low to high: text → data → BSS → heap ↑ ... ↓ stack
2.3   Text segment (.text) — compiled machine code, read-only, executable
2.4   Read-only data (.rodata) — string literals, const globals
2.5   Initialized data segment (.data) — global/static vars with non-zero init
2.6   BSS segment (.bss) — uninitialized global/static vars, zeroed by kernel
2.7   Why BSS exists — no disk space wasted for zeroed data
2.8   Heap — dynamic allocations, grows upward from end of BSS
2.9   Memory-mapped region — mmap allocations, shared libs, anonymous mappings
2.10  Stack — automatic storage, grows downward from high addresses
2.11  Kernel space — top of address space, not accessible from userspace
2.12  Reading /proc/self/maps — seeing your own process layout
2.13  /proc/self/smaps — detailed memory stats per region
2.14  Inspecting with pmap — visual address space map
2.15  The "gap" between heap and stack — virtual, not physical
2.16  Stack limit — RLIMIT_STACK, typically 8MB
2.17  Multiple threads — each thread has its own stack in the mmap region
2.18  Shared library layout — loaded into mmap region, shared across processes
2.19  Environment variables and argv — stored above stack at process start
2.20  VDSO / vsyscall — kernel-mapped code for fast syscalls (gettimeofday, etc.)
```

---

## TIER 3 — The Stack in Depth

```
3.1   What the stack is — LIFO region for function call management
3.2   Stack pointer (RSP on x86-64) — register pointing to top of stack
3.3   Frame pointer (RBP on x86-64) — register pointing to base of current frame
3.4   Stack frame (activation record) — everything pushed for one function call
3.5   Stack frame contents — return address, saved registers, locals, params
3.6   Calling conventions — who saves which registers, how args are passed
3.7   x86-64 System V ABI — args in RDI, RSI, RDX, RCX, R8, R9, rest on stack
3.8   Return values — RAX for integer/pointer, XMM0 for float
3.9   CALL instruction — pushes return address, jumps to function
3.10  RET instruction — pops return address, jumps back to caller
3.11  PUSH / POP — how values are written/read from stack
3.12  Prologue / epilogue — setup and teardown of stack frame
3.13  Red zone — 128 bytes below RSP usable without adjusting RSP (x86-64)
3.14  Stack growth direction — downward on x86/ARM/most architectures
3.15  Local variable layout — compiler assigns slots in frame
3.16  Stack canaries — sentinel value to detect overflows (-fstack-protector)
3.17  Stack overflow — recursion too deep, local too large, segfault on guard page
3.18  Stack guard page — unmapped page to catch overflows
3.19  Alloca — allocates on stack (adjusts RSP), freed on function return
3.20  VLA — variable-length array, also on stack, same risks as alloca
3.21  Non-local returns — longjmp restores saved RSP/RBP
3.22  Stack unwinding — exception handling, debugger backtraces
3.23  DWARF — debug format encoding stack layout for backtraces
3.24  Reading a stack trace — frame numbers, return addresses, function names
3.25  Never return pointer to local variable — the canonical beginner bug
3.26  Function inlining — no stack frame created, compiler optimization
3.27  Tail call optimization — callee reuses caller's frame
```

---

## TIER 4 — The Heap in Depth

```
4.1   What the heap is — region for dynamic allocations of arbitrary lifetime
4.2   brk() / sbrk() — syscalls to extend the data segment (old heap growth)
4.3   mmap() for large allocations — glibc uses mmap for >MMAP_THRESHOLD
4.4   The allocator — userspace library managing the heap (glibc malloc)
4.5   malloc chunk — header + data, chunk metadata stored before user pointer
4.6   Chunk header — size, flags (prev_inuse, is_mmapped, non_main_arena)
4.7   Free list — linked list of free chunks
4.8   Bins — categorized free lists (fast, small, large, unsorted, tcache)
4.9   Tcache — thread-local cache of freed chunks (glibc 2.26+)
4.10  Fastbins — small fixed-size free chunks, no coalescing
4.11  Smallbins — doubly-linked lists for small chunks
4.12  Largebins — sorted by size for large chunks
4.13  Unsorted bin — chunks go here first before being sorted
4.14  Coalescing — merging adjacent free chunks to reduce fragmentation
4.15  Top chunk (wilderness) — the chunk at the end of heap
4.16  malloc_trim() — returning unused heap memory to OS
4.17  malloc_stats() / mallinfo() — inspecting allocator state
4.18  malloc_usable_size() — actual usable bytes in an allocation
4.19  Heap fragmentation — many small frees leaving unusable gaps
4.20  Internal fragmentation — wasted space inside an allocation (padding)
4.21  External fragmentation — free space exists but not contiguous enough
4.22  Heap exhaustion — malloc returns NULL, must always check
4.23  Heap overflow — writing past end of allocation, corrupts metadata
4.24  Use-after-free — heap metadata/data corruption, security exploit class
4.25  Double free — corrupts free list, classic exploit primitive
4.26  Heap spray — attacker technique to position data predictably
4.27  MALLOC_CHECK_ / MALLOC_PERTURB_ — glibc debug env vars
4.28  Electric fence / DUMA — each allocation on its own page, detect overflows
```

---

## TIER 5 — Pointer Fundamentals

```
5.1   What a pointer is — a variable whose value is a memory address
5.2   Pointer size — sizeof(void*) == 4 on 32-bit, 8 on 64-bit
5.3   Pointer declaration syntax — T *p (binds to name, not type)
5.4   Reading complex declarations — right-to-left rule
5.5   Address-of operator & — gives address of a variable
5.6   Dereference operator * — reads/writes value at address
5.7   The pointer/pointee distinction — pointer is the variable, pointee is what it points at
5.8   Initialization — always initialize pointers, uninitialized = wild pointer
5.9   NULL — the null pointer constant, 0 cast to pointer
5.10  NULL representation — guaranteed to compare unequal to any valid pointer
5.11  Null pointer deref — SIGSEGV, always check before dereferencing
5.12  Printing pointers — %p format, cast to void* first
5.13  Pointer assignment — p = q makes p point to what q points to
5.14  Pointer comparison — == != < > only valid within same array
5.15  Pointer to pointer — T **pp, what it means, why it's needed
5.16  Triple pointer — T ***ppp, usually a design smell
5.17  Returning a pointer from a function — heap only, never stack locals
5.18  The "swap two ints" example — canonical first pointer exercise
5.19  Simulating pass-by-reference — passing &x, modifying *x in function
```

---

## TIER 6 — Pointer Arithmetic

```
6.1   Pointer arithmetic rules — p + n moves by n * sizeof(*p) bytes
6.2   Why it scales by sizeof — pointers know their pointee type
6.3   p++ — advances by sizeof(*p) bytes
6.4   p-- — moves back by sizeof(*p) bytes
6.5   Pointer difference — (p - q) gives count of elements, type ptrdiff_t
6.6   Valid arithmetic range — within array + one past end
6.7   One-past-end pointer — valid to form, invalid to dereference
6.8   Walking an array with pointer — while (p < end) *p++ = 0
6.9   Pointer arithmetic on void* — illegal (GCC extension allows it, avoid)
6.10  Pointer arithmetic on char* — always 1 byte per increment
6.11  Pointer arithmetic and struct layout — not valid across struct members
6.12  Subtraction to get offset — (char*)p - (char*)base
6.13  Comparing pointers to different objects — undefined behavior
6.14  Array indexing is pointer arithmetic — a[i] == *(a + i) == i[a]
6.15  Negative indices — valid if pointer points far enough into array
6.16  Two-pointer technique — classic algorithm pattern
```

---

## TIER 7 — Pointer Declarations (All Forms)

```
7.1   int *p           — pointer to int
7.2   int **p          — pointer to pointer to int
7.3   int *p[10]       — array of 10 pointers to int
7.4   int (*p)[10]     — pointer to array of 10 ints
7.5   int *f()         — function returning pointer to int
7.6   int (*f)()       — pointer to function returning int
7.7   int (*f)(int,int)— pointer to function taking two ints, returning int
7.8   int *(*f)(int)   — pointer to function returning pointer to int
7.9   int (*p[5])(int) — array of 5 pointers to functions
7.10  const int *p     — pointer to const int (can't modify pointee)
7.11  int * const p    — const pointer to int (can't modify pointer)
7.12  const int * const p — const pointer to const int (neither modifiable)
7.13  int (* const p)(int) — const function pointer
7.14  void *p          — generic pointer, no arithmetic, no dereference
7.15  Using cdecl tool — parsing insane declarations automatically
7.16  typedef to simplify — typedef int (*Comparator)(const void*, const void*)
```

---

## TIER 8 — const and Pointers

```
8.1   const T *p — read-only view of pointee, pointer itself is mutable
8.2   T * const p — pointer is fixed, pointee is mutable
8.3   const T * const p — both fixed
8.4   Passing const T* to functions — communicates read-only intent
8.5   Returning const T* — caller cannot modify through it
8.6   const-correctness — discipline of propagating const through all code
8.7   Casting away const — (T*)const_ptr — legal syntax, UB if you actually write
8.8   String literals and const — char *p = "hello" — should be const char*
8.9   const and arrays — const int arr[] means elements are const
8.10  Pointer to const vs const pointer — frequent source of confusion
8.11  Why const propagation matters — compiler optimizations rely on it
```

---

## TIER 9 — void* and Generic Pointers

```
9.1   void* — pointer to unknown type
9.2   Implicit conversion — any pointer implicitly converts to/from void* in C
9.3   No arithmetic on void* — undefined (GCC extension allows, -Wpedantic warns)
9.4   No dereference of void* — must cast first
9.5   malloc returns void* — no cast needed in C (required in C++)
9.6   Using void* for generics — qsort, bsearch, callback context
9.7   The context/userdata pattern — void* carrying caller state into callbacks
9.8   Type punning via void* — casting through void* does NOT bypass aliasing
9.9   Function pointer vs void* — function pointers are not void* (different size possible)
9.10  NULL as void* — (void*)0
```

---

## TIER 10 — Arrays and Pointers

```
10.1  Array decay — array name in expression becomes pointer to first element
10.2  What decays — array name in most expression contexts
10.3  What does NOT decay — sizeof(arr), &arr, string literal init of char[]
10.4  sizeof array vs sizeof pointer — the critical difference
10.5  &arr vs arr — &arr is T(*)[N], arr is T* — different types, same address
10.6  Arrays are NOT pointers — they are different types, just often compatible
10.7  Passing arrays to functions — always decays to pointer, size information lost
10.8  Passing size separately — canonical pattern: f(int *arr, size_t n)
10.9  2D arrays — T a[R][C] is contiguous, a[i][j] == *(*(a+i)+j)
10.10 Pointer to row of 2D array — int (*p)[C] = a
10.11 Array of pointers — int *p[R], each pointing to separate allocation
10.12 The difference in memory layout — contiguous vs scattered
10.13 Jagged arrays — array of pointers to arrays of different lengths
10.14 Multidimensional array decay — only first dimension decays
10.15 Returning array from function — impossible directly, use pointer or struct
10.16 Flexible array member — struct { int n; int data[]; } — C99
10.17 Zero-length arrays — GCC extension, use FAM instead
10.18 String as array of char — null-terminated, every string is a char*
```

---

## TIER 11 — Function Pointers

```
11.1  What a function pointer is — address of a function's machine code
11.2  Declaring a function pointer — int (*fp)(int, int)
11.3  Assigning — fp = &add or fp = add (same thing in C)
11.4  Calling — (*fp)(1,2) or fp(1,2) (same thing in C)
11.5  typedef for clarity — typedef int (*BinOp)(int, int); BinOp fp = add
11.6  Passing as argument — callbacks, generic algorithms
11.7  Returning from function — factory pattern
11.8  Array of function pointers — dispatch table, state machine
11.9  Struct of function pointers — C vtable, simulating methods
11.10 NULL function pointer — check before calling
11.11 Function pointers vs void* — not guaranteed same size (POSIX requires it)
11.12 Casting function pointers — undefined behavior in general, POSIX exception
11.13 dlsym() — loading function pointer at runtime from shared library
11.14 Signal handlers as function pointers — void (*)(int)
11.15 qsort comparator — classic function pointer callback example
11.16 Computed goto (GCC) — labels as values, pointer to label, dispatch table
```

---

## TIER 12 — Struct Pointers and Memory Layout

```
12.1  Pointer to struct — struct Foo *p, use -> to access members
12.2  -> operator — p->field is (*p).field exactly
12.3  Struct size — sum of member sizes + padding
12.4  Alignment requirement — each member must start at multiple of its alignment
12.5  Padding — compiler inserts unused bytes to satisfy alignment
12.6  Trailing padding — struct padded to multiple of its largest member's alignment
12.7  Example — struct {char a; int b} has 3 bytes padding after a
12.8  sizeof surprises — struct size ≠ sum of member sizes
12.9  offsetof(struct, member) — byte offset of a member
12.10 Manual padding control — reorder members to minimize padding
12.11 __attribute__((packed)) — eliminate padding (alignment penalty, UB risk)
12.12 alignas(N) — force member or variable to specific alignment (C11)
12.13 Pointer to member — &p->field gives address of that field
12.14 Pointer aliasing via struct — accessing struct through incompatible type = UB
12.15 container_of macro — given pointer to member, get pointer to containing struct
12.16 container_of implementation — (Type*)((char*)ptr - offsetof(Type, member))
12.17 Intrusive linked lists — embedding list node inside struct, used in Linux kernel
12.18 Forward declaration — struct Foo; lets you use Foo* before defining struct
12.19 Opaque pointer pattern — hide struct behind typedef in header, define in .c
12.20 Self-referential struct — struct Node { int val; struct Node *next; }
12.21 Pointer to union — accessing via wrong union member through pointer = UB
12.22 Bit field pointers — you cannot take address of a bit field
```

---

## TIER 13 — Memory Alignment in Depth

```
13.1  What alignment is — objects must start at addresses divisible by their alignment
13.2  Natural alignment — int aligned to 4, double to 8, pointer to 8 (on 64-bit)
13.3  _Alignof(T) — alignment requirement of type T
13.4  _Alignas(N) — specify alignment of a variable or struct member
13.5  aligned_alloc(align, size) — heap allocation with guaranteed alignment (C11)
13.6  posix_memalign() — POSIX aligned allocation
13.7  Why alignment matters — misaligned access: slow (x86), bus error (ARM)
13.8  SIGBUS — signal for misaligned access on strict architectures
13.9  Packed structs and alignment — __attribute__((packed)) can cause misalignment
13.10 DMA and alignment — device memory often requires specific alignment
13.11 SIMD alignment — SSE requires 16-byte, AVX requires 32-byte alignment
13.12 Stack alignment — x86-64 ABI requires 16-byte alignment at CALL
13.13 Checking alignment at runtime — ((uintptr_t)p & (align-1)) == 0
13.14 max_align_t — type with maximum fundamental alignment
13.15 Alignment and casting — casting to stricter alignment = UB if not aligned
13.16 struct padding to ensure alignment — compiler adds trailing padding
13.17 Allocator alignment guarantee — malloc returns at least max_align_t aligned
13.18 Page alignment — mmap returns page-aligned (4096 bytes)
```

---

## TIER 14 — Strict Aliasing

```
14.1  What aliasing is — two pointers referring to the same memory
14.2  The strict aliasing rule — an object shall only be accessed through its effective type
14.3  Effective type — the type of the object as it was last stored to
14.4  Why the rule exists — enables compiler to assume two different-type pointers don't alias
14.5  Optimization consequence — compiler may reorder, cache, or eliminate loads/stores
14.6  The classic violation — int i; float *fp = (float*)&i; *fp = 1.0f; *i = ... (UB)
14.7  What types may alias — exhaustive list from C standard §6.5p7:
        - compatible type
        - signed/unsigned version of same type
        - qualified version (const, volatile)
        - aggregate or union containing compatible type
        - char, unsigned char, signed char (always may alias anything)
14.8  char* exception — char* can alias any type, used in memcpy
14.9  unsigned char* — safe to inspect any object byte-by-byte
14.10 void* — does not bypass strict aliasing, must cast to actual type first
14.11 The -fstrict-aliasing flag — enabled by default at -O2 and above
14.12 -fno-strict-aliasing — disables the rule, used by Linux kernel
14.13 -Wstrict-aliasing — compiler warning for aliasing violations
14.14 Real-world breakage — code that worked at -O0 breaks at -O2
14.15 The optimizer's view — alias analysis pass in LLVM/GCC
14.16 Detecting violations — TySan (type sanitizer, experimental)
```

---

## TIER 15 — Type Punning

```
15.1  What type punning is — treating the same bytes as a different type
15.2  Why you'd want it — float bits, network protocol parsing, hashing
15.3  The WRONG way — float f = 1.0; int i = *(int*)&f — strict aliasing violation
15.4  The RIGHT way (C99+) — union type punning
15.5  Union type punning — write one member, read another — defined in C, not C++
15.6  The RIGHT way (always safe) — memcpy into target type
15.7  memcpy for type punning — compiler optimizes away the copy (no overhead)
15.8  Example — inspecting float bits: memcpy(&u32, &f32, 4)
15.9  Why memcpy works — reads/writes as char*, which bypasses strict aliasing
15.10 __builtin_memcpy — GCC/Clang intrinsic, same semantics, often better codegen
15.11 Trap representations — not all bit patterns are valid for all types
15.12 Endianness matters in type punning — bytes may be in different order
15.13 Portability — union punning is C99 defined, not C++ defined
15.14 Compilers in practice — all major compilers accept union punning
15.15 -fno-strict-aliasing workaround — disables optimization, not recommended
```

---

## TIER 16 — restrict

```
16.1  What restrict means — this pointer is the only way to access this memory in this scope
16.2  restrict is a promise from programmer to compiler
16.3  Consequence — compiler may optimize assuming no aliasing with restricted pointer
16.4  restrict in function parameters — memcpy(void * restrict dst, const void * restrict src, size_t n)
16.5  restrict on local variables — less common, still valid
16.6  What happens if you lie — undefined behavior, silent wrong results
16.7  memcpy vs memmove — memcpy has restrict, memmove does not (handles overlap)
16.8  FORTRAN comparison — restrict gives C FORTRAN-level aliasing guarantees
16.9  Auto-vectorization — restrict enables compiler to generate SIMD code
16.10 restrict and pointers to pointers — T * restrict *pp (rare)
16.11 Checking restrict correctness — no tool enforces it, manual discipline only
16.12 restrict is C99 — not in C89, not in C++ (but compilers support __restrict)
```

---

## TIER 17 — volatile and Pointers

```
17.1  What volatile means — every access must go to memory, no caching in registers
17.2  When volatile is needed — hardware registers, signal handlers, setjmp
17.3  volatile T *p — pointer to volatile object
17.4  volatile and optimization — compiler must not reorder or eliminate accesses
17.5  volatile is NOT atomic — two threads accessing volatile = data race = UB
17.6  volatile is NOT a memory barrier — CPU can still reorder
17.7  volatile vs _Atomic — volatile for hardware/signals, _Atomic for threading
17.8  Memory-mapped I/O — volatile uint32_t *reg = (volatile uint32_t *)0xDEAD0000
17.9  Signal handlers — volatile sig_atomic_t flag = 0 — correct pattern
17.10 setjmp/longjmp interaction — locals must be volatile to survive longjmp
17.11 volatile in device drivers — every register access must actually happen
17.12 The Linux kernel's READ_ONCE/WRITE_ONCE — portable volatile access macros
17.13 Common mistake — using volatile for thread communication (use _Atomic)
```

---

## TIER 18 — Pointer Provenance (Abstract Machine Model)

```
18.1  What provenance is — a pointer carries the identity of its source allocation
18.2  Why provenance exists — enables alias analysis and optimization
18.3  The problem — two pointers with same address but different provenance
18.4  Example — uintptr_t u = (uintptr_t)p; int *q = (int*)u; — q has no provenance
18.5  Pointer-to-integer-to-pointer — roundtrip may lose provenance (UB in strict model)
18.6  PNVI-ae-udi — proposed provenance model (C standards committee)
18.7  What compilers do today — gcc/clang allow most roundtrips in practice
18.8  Why it matters for systems code — OS kernels, allocators, JITs use int-ptr casts
18.9  __builtin_launder (C++) — hints about provenance, no C equivalent
18.10 The "effective type" connection — provenance determines what types are valid
18.11 Practical advice — avoid int-pointer casts unless you control optimization flags
18.12 LLVM's treatment — LLVM IR has provenance semantics in its pointer model
18.13 Ongoing standardization — C23 / C2y still debating the exact model
```

---

## TIER 19 — Pointer Bugs in Depth

### Dangling Pointers
```
19.1  Dangling pointer — pointer to memory that is no longer valid
19.2  Dangling to stack — returning pointer to local variable
19.3  Dangling to freed heap — use-after-free
19.4  Use-after-free — reading/writing freed memory, heap corruption or exploit
19.5  Dangling after realloc — old pointer invalid if realloc moves allocation
19.6  Detecting dangling — set to NULL after free, ASan, valgrind
19.7  NULL after free — does NOT prevent dangling if pointer was aliased
```

### Wild Pointers
```
19.8  Wild pointer — uninitialized pointer, value is garbage
19.9  Deref of wild pointer — UB, segfault if lucky, silent corruption if not
19.10 Detection — -Wuninitialized, valgrind, MSan
```

### Buffer Overflows
```
19.11 Stack buffer overflow — overwriting return address, saved RBP, canary
19.12 Stack smashing — classic exploit, overwrite return address with shellcode
19.13 Heap buffer overflow — overwriting chunk metadata, adjacent allocations
19.14 Off-by-one — writing one byte past end (off-by-one null write is often exploitable)
19.15 Integer overflow leading to underallocation — malloc(n * sizeof(T)) where n overflows
19.16 Format string vulnerability — printf(user_input) reads/writes stack
19.17 Bounds checking — no automatic, must be done manually every time
```

### Double Free
```
19.18 Double free — calling free() twice on same pointer
19.19 Effect — corrupts allocator free list, heap metadata
19.20 Exploitation — double free is a powerful exploit primitive
19.21 Prevention — set pointer to NULL immediately after free
```

### NULL Dereference
```
19.22 NULL deref — accessing address 0, always SIGSEGV
19.23 NULL page — on Linux, first page is unmapped (can be changed via vm.mmap_min_addr)
19.24 Kernel NULL deref — historically exploitable, now mitigated
```

### Memory Leaks
```
19.25 Memory leak — allocation without corresponding free
19.26 Gradual leak — accumulates over time, eventually OOM
19.27 One-time leak — allocated once, freed on exit (acceptable in some contexts)
19.28 Detecting leaks — valgrind --leak-check=full, ASan leak sanitizer
```

---

## TIER 20 — Memory Debugging Tools

```
20.1  valgrind memcheck — invalid reads, invalid writes, use-after-free, leaks
20.2  valgrind output — reading error reports, suppression files
20.3  ASan (AddressSanitizer) — compile-time, -fsanitize=address
20.4  ASan shadow memory — 1/8 of address space used to track allocations
20.5  ASan redzones — poisoned bytes around allocations detect overflows
20.6  MSan (MemorySanitizer) — uninitialized reads, -fsanitize=memory
20.7  UBSan (UndefinedBehaviorSanitizer) — catches many UB cases at runtime
20.8  TSan (ThreadSanitizer) — data race detection, -fsanitize=thread
20.9  Electric Fence — each allocation gets its own page, deref past end = segfault
20.10 DUMA — like Electric Fence, also catches underwrites
20.11 GDB — watchpoints on memory addresses, catching writes
20.12 GDB heap commands — info malloc, heap debug commands
20.13 /proc/<pid>/maps — see all memory regions of a process
20.14 /proc/<pid>/smaps — per-region memory stats (RSS, PSS, dirty pages)
20.15 pmap — command-line process memory map viewer
20.16 Massif (valgrind) — heap profiler, peak heap usage
20.17 heaptrack — fast heap profiler, flamegraph output
20.18 mtrace — glibc malloc tracing (MALLOC_TRACE env var)
20.19 MALLOC_CHECK_ — glibc env var to enable extra heap checks
20.20 clang static analyzer — finds bugs without running code
20.21 cppcheck — static analysis for C, pointer bugs
20.22 Sparse — semantic checker used by Linux kernel
```

---

## TIER 21 — Dynamic Memory — The Full API

```
21.1  malloc(size) — allocate size bytes, uninitialized, returns NULL on failure
21.2  calloc(n, size) — allocate n*size bytes, zero-initialized, overflow-safe multiply
21.3  realloc(ptr, size) — resize allocation, may move, old pointer invalid after call
21.4  realloc return value — always use temporary: tmp = realloc(p, n); if(!tmp) ...
21.5  free(ptr) — release allocation, ptr must be from malloc/calloc/realloc
21.6  free(NULL) — always safe, no-op
21.7  aligned_alloc(align, size) — C11, alignment must be power of two, size multiple of align
21.8  posix_memalign(&ptr, align, size) — POSIX, align must be power of two ≥ sizeof(void*)
21.9  valloc(size) — page-aligned allocation (obsolete, avoid)
21.10 memalign(align, size) — like posix_memalign but older API
21.11 alloca(size) — stack allocation, freed on function return, no failure return
21.12 malloc_usable_size(ptr) — glibc extension, actual bytes in chunk
21.13 malloc_trim(pad) — return free memory to OS
21.14 mallopt() — tuning malloc parameters (M_MMAP_THRESHOLD, M_TRIM_THRESHOLD)
21.15 mallinfo() / mallinfo2() — heap statistics struct
```

---

## TIER 22 — Custom Allocators

```
22.1  Why custom allocators — performance, locality, determinism, debugging
22.2  Arena allocator — large slab, bump pointer, free all at once
22.3  Arena implementation — char *base, *cur, *end; void* alloc(size_t n)
22.4  Arena advantages — O(1) alloc, zero fragmentation, O(1) free-all
22.5  Arena use cases — request-scoped data, parser, game frame
22.6  Pool allocator — fixed-size objects, free list, O(1) alloc/free
22.7  Pool implementation — intrusive free list, objects store next pointer when free
22.8  Pool advantages — no fragmentation for fixed size, cache-friendly
22.9  Pool use cases — connection objects, AST nodes, fixed-size messages
22.10 Stack allocator — push/pop allocations, lifo only
22.11 Slab allocator — kernel-style, cache-aware, object constructor/destructor
22.12 Buddy allocator — powers-of-two sizes, fast coalescing
22.13 Freelist allocator — general purpose, best-fit or first-fit
22.14 Memory tagging — tag pointers with allocation ID for debugging
22.15 Ownership tracking in allocator — knowing who allocated what
22.16 Thread-local allocator — per-thread slab to avoid locking
22.17 Scope-based allocation — C++ RAII style simulated with cleanup attribute
22.18 GCC cleanup attribute — __attribute__((cleanup(fn))) automatic free on scope exit
22.19 Obstack — GNU library for stack-discipline arena allocator
```

---

## TIER 23 — Advanced Pointer Techniques

```
23.1  Tagged pointers — using low bits of aligned pointer to store flags
23.2  Why it works — aligned pointers have 0 in low bits (e.g. 3 bits free for 8-byte aligned)
23.3  Extracting tag — ptr & 0x7
23.4  Extracting address — ptr & ~0x7
23.5  Use cases — NaN-boxing (JavaScript engines), GC mark bits, lock-free algorithms
23.6  Fat pointers — pointer + length + metadata in a struct
23.7  XOR linked list — node stores prev XOR next, saves one pointer per node
23.8  Sentinel nodes — dummy head/tail nodes simplify linked list logic
23.9  Self-referential pointers — pointer within struct pointing back to itself or parent
23.10 Handle tables — integer keys into array of pointers (avoids pointer exposure)
23.11 Relative pointers — store offset from base instead of absolute address (relocatable)
23.12 Compressed pointers — storing 32-bit offset into known base (JVM compressed oops)
23.13 Pointer swizzling — converting file offsets to pointers on load (mmap'd databases)
23.14 Interior pointers — pointing into the middle of an allocation
23.15 Pointer reversal — Deutsch-Schorr-Waite graph traversal without recursion or stack
23.16 Lock-free pointer operations — CAS on pointers, ABA problem
23.17 ABA problem — pointer value cycles back, CAS falsely succeeds
23.18 Hazard pointers — safe memory reclamation in lock-free structures
23.19 RCU (Read-Copy-Update) — pointer publishing protocol (Linux kernel)
23.20 Memory-mapped pointer — pointer into mmap'd file, persists across runs
23.21 Capability pointers — hardware-enforced bounds checking (CHERI architecture)
```

---

## TIER 24 — Pointer Safety Patterns & Idioms

```
24.1  Always initialize — T *p = NULL; never leave uninitialized
24.2  Always check malloc — if (!p) { handle error }
24.3  Null after free — free(p); p = NULL; (only helps if not aliased)
24.4  Single ownership — one owner per allocation, clear who frees
24.5  Ownership transfer — documented in function signature/comment
24.6  const for read-only access — communicate intent, enable optimization
24.7  Bounds always paired — T *buf, size_t buflen — always together
24.8  Never return pointer to local — return heap or static only
24.9  Don't hold pointer across realloc — realloc may invalidate
24.10 Opaque pointer pattern — hide internals, control lifetime
24.11 Cleanup goto pattern — single exit point ensures all pointers freed
24.12 Two-phase init — allocate, then initialize — separate concerns
24.13 Pointer validation — check alignment, check range, check against known bounds
24.14 Guard pages — mprotect PROT_NONE pages around sensitive allocations
24.15 Memory ownership documentation — comments: "caller must free", "owned by X"
24.16 Const-correct API — inputs as const T*, outputs as T*
24.17 Avoid aliasing in API — don't allow input and output to overlap unless documented
24.18 Compiler annotations — __attribute__((nonnull)), __attribute__((malloc))
24.19 Static analysis — clang-tidy, cppcheck, PVS-Studio pointer checks
24.20 Fuzzing pointer-heavy code — libFuzzer, AFL++ catch memory bugs
```

---

## TIER 25 — Pointers in the C Memory Model (Concurrency)

```
25.1  Data race — two unsynchronized concurrent accesses where at least one is write
25.2  Data race on a pointer — UB even if "just reading the address"
25.3  Pointer publishing — making a new allocation visible to other threads
25.4  Release-acquire — writer does atomic_store(release), reader does atomic_load(acquire)
25.5  The message-passing pattern — publish pointer via atomic, guarantee pointee is ready
25.6  _Atomic(T*) — atomic pointer type
25.7  atomic_store / atomic_load — on pointer type
25.8  compare_exchange — atomic pointer CAS, foundation of lock-free structures
25.9  Hazard pointers — safe pointer deref in lock-free code
25.10 The read-side memory ordering problem — why relaxed is not enough for pointers
25.11 Volatile is not enough — volatile does not create synchronization
25.12 Signal handler and volatile — sig_atomic_t for flags, not for pointers
25.13 Memory barriers — __atomic_thread_fence, atomic_signal_fence
25.14 Thread-local storage — __thread, _Thread_local, each thread's own pointer
25.15 TSan — detecting pointer races at runtime
```

---

## Quick Reference: What Lives Where

```
REGION       | WHO ALLOCATES | WHO FREES     | LIFETIME
-------------|---------------|---------------|--------------------
Registers    | Compiler      | Compiler      | Within expression
Stack        | Compiler      | Compiler      | Until function returns
BSS/Data     | OS at load    | OS at exit    | Entire program
Heap         | You (malloc)  | You (free)    | Until you free it
mmap         | You (mmap)    | You (munmap)  | Until you unmap it
```

```
POINTER TYPE      | WHAT IT POINTS TO         | VALID AS LONG AS
------------------|---------------------------|----------------------
Stack pointer     | Local variable            | Function is on stack
Heap pointer      | malloc'd allocation       | Not freed
Static pointer    | Global/static variable    | Always
String literal    | .rodata segment           | Always (read-only)
NULL              | Nothing                   | Never dereference
Dangling          | Freed/gone memory         | Never
Wild              | Garbage address           | Never
```

---

**~280 topics across 25 tiers.** This is the complete map from transistors to lock-free pointer algorithms.

Which tier do you start with?
