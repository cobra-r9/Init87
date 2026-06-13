# this is a comment in assembly;
# we will be using the gnu as for compiling the assembly code. 
# this is the first assembly program.

# the assembly has many sections.
# the global constants and strings are stored in the .section .data under a label.
# we would be creating an ascii string. "Hello Assembly" for example. 

.section .data
# create a label for ascii, I call it msg 
# this has a permission r__ 
msg:
    # now we will store the string using the ascii 
    .ascii "Hello Assembly!!!\n"
    # unlike asciz which will add the newline itself, we use ascii. 
    # now that we need to calculate the length of this text (ie the size in bytes)
    # for that we are gonna use the len variable to store its size. 
    len = . - msg
    # this simply means, we need to look in the current address : msg, (.), and calculate the length. 
    # now that after calculating the length, we need to switch to the .text section, which contains the actual executable code. 
.section .text
# this .text section is the start of the actual executable code; it has a permission : rx_ 
.globl _start 
_start:
    # this simply means, we are telling the assembler that _start is the start of the program. 
    # inside the start label, we initialise the program. 
    # we need to know about the syntax of moving values to the registers first. 
    # before that we would need to know about the registers.
    # there are various special purpose as well as general purpose registers.
    # some special purpose registers are the PC : program counter, etc stuffs. 
    # general purpose registers includes rax, rdi, rsi, rdx, etc registers.
    # the syscall number goes into the rax register.
    # once the syscall completes, the return value goes into the rax register again, overwriting the syscall number.
    # the first agrument of the syscall goes into the rdi register.
    # the second one goes into the rsi 
    # the 3rd one goes into the rdx register. 
    # and for calling a syscall, we just use syscall to call it. 
    # we need to know about linux syscalls for that reason.
    # the syscall for write is 1; the syscall number for exit is 60;
    # the syntax of the syscall in C is :
    #   for write, it is : write(int fd, char *msg, size_t bytes)
    #   for exit, it is : exit(int exit_code);
    # therefore we will be using all the four registers to just print the output.
    # fd 1 means it will be printed to the stdout. 

    # step 1 : set the syscall. we will move the value into register using movq. q suffix means the quad word = 64 word size. 
    # essentially, the write syscall is 4 assembly instructions, excluding the syscall itself.
    movq $1, %rax
    # syntax is instruction <word/variable/pointer>, %register
    # the above will move constant 1 into rax, setting the syscall to write. 
    movq $1, %rdi 
    movq $msg, %rsi
    # $msg means - provide me the pointer to the msg.
    movq $len, %rdx
    # $len means - constant length/size of the msg. 
    # it is based on the context.
    # information = bits + context.
    # the above 3 assembly instructions will move the argument 1, 2, 3 of the syscall write into the respecitve registers as mentioned above. 

    syscall
    # finally execute the syscall;
    # the return value of the syscall is overwrites the rax. 

    # step 2 : exit syscall. exit(0)
    # the exit syscall is 2 assembly instructions excluding the syscall itself. 
    movq $60, %rax 
    # set syscall for exit 
    movq $0, %rdi 
    # set the first argument.
    syscall 
    # execute the syscall.
    # the kernel is trapped again.

# woosh, and we have completed programming our first assembly code. 
# for running this assembly code, we would first asseble it into the object file.
# then we would link it with the ld.
#
