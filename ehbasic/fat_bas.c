#include "fat_bas.h"
#include <stdio.h>

int fileopen = 0;
FIL file;

BYTE loadFile(char *filename)
{
    char c;

    if (!fileopen)
    {
        FRESULT res = f_open(&file, filename, FA_OPEN_EXISTING | FA_READ);

        if (res != FR_OK)
        {
            printf("\r\nFile not found Error.\r\n");
            return '~';
        }
        fileopen = 1;
    }

    UINT *br;
    FRESULT res = f_read(&file, &c, 1, br);

    if (res != FR_OK)
        c = '~';

    if (c == '~')
    {
        f_close(&file);
        fileopen = 0;
        printf("%d bytes loaded.\r\n", f_size(&file));
    }

    return c;
}

int saveFile(char *filename, char *c)
{

    if (!fileopen)
    {
        FRESULT res = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);

        if (res != FR_OK)
        {
            printf("\r\nFile not found Error.\r\n\r\n");
            return '~';
        }
        fileopen = 1;
    }

    UINT bw;

    FRESULT res = f_write(&file, c, 1, &bw);

    if (*c == '~' )
    {
        f_close(&file);
        fileopen = 0;
        printf("\r\n%d bytes saved.\r\n", f_size(&file));
    }

    return *c;
}

int deleteFile(char *filename)
{

    return f_unlink(filename);
}
