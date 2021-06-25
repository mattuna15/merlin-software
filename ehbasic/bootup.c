#include <stdio.h>

extern void EHBEGIN(void);

int main() {

    void (*code_ptr)(int) = &EHBEGIN;

    printf("\r\n\r\nStart of code is 0x%lX\n", code_ptr);

    printf("\r\nStarting Merlin Bios.\r\n");

    printf("\r\nLoading Basic.\r\n");

    EHBEGIN();

    printf("\r\nShouldn't get here.\r\n");

}