.section .data # this is the data section. 
msg: # create a label called msg in the data section. 
    .ascii "Hello, World!\n" # create an ascii string, stored under label msg 
    len = . - msg # this len . says to look in current address, in msg, and len calculates its size (bytes)

.section .text # back to the text section 
.global _start

_start:
    # we will be writing linux syscalls. 
    # the syscall here is write(fd, msg, bytes to write)
    # as we know, from previous file lessons, fd for stdout is 1.
    # we need to provide pointer to msg, and the bytes to write; 
    # the syscall number/return value goes to the rax register
    # registers are prefixed with % in GNU as. 
    # we need to move a quad value into that register. 
    # we use movq to move a quad word = 64 bits into that register which tells the size of the operation being performed. 
    movq $1, %rax 
    # now that we have write(...)
    # next step is the first argument of the syscall, which goes into rdi register by convention. 
    movq $1, %rdi 
    # this is the first argument. moving 1 into first argument - ie, the fd, which is stdout = terminal. 
    # the second argument goes into the rsi register. which is pointer to msg. $msg is pointer to msg. 
    # and that our msg has a ascii string. 
    movq $msg, %rsi
    # then we need the bytes to write. which is len, goes into third argument : register is rdx
    movq $len, %rdx
    # now that we have filled all our arguments, time for us to call the write syscall.
    # we can call the syscall by using syscall 
    syscall

    # now that the syscall is over, we need to exit the program. 
    # we use the exit syscall. 
    # the syscall number of exit is 60.
    # it takes one argument which is the return value or exit number 
    movq $60, %rax 
    movq $0, %rdi
    syscall
    # kernel trapped again. 
