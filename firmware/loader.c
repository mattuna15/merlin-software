#include "../ehbasic/firmware-array.h"
#include "../tutor/tutor-array.h"
#include <string.h>
#include <stdio.h>

int main()
{

    char c = '0';

    puts("\r\nMerlin 1.0 Dec 2021\r\nChoose option\r\n");
    puts("\r\n1. Basic\r\n2. Tutor\r\n3. Monitor\r\n4. Load SRec\r\n");

    while (1)
    {
        c = getchar();

        putchar(c);

        if (c == 0x31)
        {
            memcpy((void *)0x400, (void *)eprom, sizeof(eprom));
            asm("movea.l #0xdffffe,%sp\n\t"
                "movea.l #0x400,%a0\n\t"
                "jmp     (%a0)");
            return 0;
        }
        else if (c == 0x32)
        {
            memcpy((void *)0x1000, (void *)tutor_eprom, sizeof(tutor_eprom));
            asm("movea.l #0xdffffe,%sp\n\t"
                "movea.L #0x1146,%a0\n\t"
                "jmp     (%a0)");
            return 0;
        }
        else if (c == 0x33)
        {

            asm("movea.l #0xdf0000,%sp\n\t"
                "movea.L #0xe00bc0,%a0\n\t"
                "jmp     (%a0)");
            return 0;
        }
        else if (c == 0x34)
        {
            putchar('l');
            asm("movea.l #0xdf0000,%sp\n\t"
                "movea.L #0xe00e72,%a0\n\t"
                "jsr     (%a0)\n\t"
                "movea.L #0x400,%a0\n\t"
                "jmp (%a0)");
            return 0;
        } else {
            puts("\r\n1. Basic\r\n2. Tutor\r\n3. Monitor\r\n4. Load SRec\r\n");
        }
    }
}