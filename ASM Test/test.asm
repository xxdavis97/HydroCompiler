global _start
; https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit
_start
; need to set "a" register (rax) to move the syscall code from above table into rax
; 60 is the sys call digit for "exit"
; eax would be also register a but only 32 bit so half of the same space 
    mov rax, 60 
; now need to set "d register (rdi) as that's where arg 0 goes according to table above
; rdi wraps at 256 so 255 is max number
    mov rdi, 4
    syscall