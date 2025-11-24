section .data
    align 4
    convert: dd 0.2777777777777778

section .text
global compute_acceleration_asm
    
compute_acceleration_asm:
    push rbp
    mov rbp, rsp
    
    movss xmm3, [convert] 

    xor r8, r8 
    mov r9, 0
    
L1:
    cmp r8, rdx
    jge L2

    movss xmm0, [rdi + r9]
    movss xmm1, [rdi + r9 + 4]
    movss xmm2, [rdi + r9 + 8]
    subss xmm1, xmm0
    movss xmm4, xmm1
    mulss xmm4, xmm3

    divss xmm4, xmm2
    roundss xmm4, xmm4, 8
    cvttss2si eax, xmm4 
    mov [rsi + r8*4], eax   
    
    add r9, 12
    inc r8
    jmp L1
L2:
    pop rbp
    ret