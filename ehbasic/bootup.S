#include "asm.h"
#include <stdio.h>


        .title "Merlin bootup"

        .global main
        .extern SYM (code_start)
        .extern SYM (printf)
        .extern SYM (exit)

        .text
main:                                   
        pea     message                
        jsr printf                    

        jmp code_start

        jmp exit

message:
        .asciz "Merlin Bios. Starting Basic."  
        