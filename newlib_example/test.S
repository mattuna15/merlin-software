#include "asm.h"
#include <stdio.h>

        .global main

        .text

.LC0:
        .string "\r\nhello\r\n"
main:
        pea .LC0
        jsr printf
        addq.l #4,%sp
        clr.l %d0
        rts