Here it is, the initv1.c, a C source file. A C source file would have to pass through 4 phases to finally become an executable binary.

1) cpp : eah, it is a tool, the c pre processor. when you call the gcc, the cpp first executes, does all the copy pasta stuffs in the include headers, removing comments and then replacing macros and code blocks. 

This produces the exact file just before it is compiled to assembly. We can stop here to see how it looks like by doing gcc -E flag. 

2) cc : c compiler, this compiles the full C preprocessed code into an assembly code : .asm. To see this assembly code, we use gcc -S flag. Note, yet here there is nothing linked, noting replaced, just whatever is in the pre processed code, that would be in assembly.

3) asm : the assembler, which will transform the assembly code into a ROP (relocatable object file), which is not the final binary, but it has some unknown or unresolved functions which have been declared, but not yet resolved to definition. In the sense as it is relocatble, the `ld` : linux static linker will patch those unresolved functions by linking the gaps to the glibc : gnu standard C library object file (precompiled library) to finx it. Stop at -c flag. 

4) the fixing work is done by the linker, which links the unresolved functions to required libraries. pass nothing, but compile.
