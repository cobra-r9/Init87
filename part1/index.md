

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

