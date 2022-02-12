#include <stdio.h>
#include <string.h>
#include "fat_bas.h"
#include "fat_compat.h"

int fileopen = 0;
FIL file;

int initDrive()
{

    if (FindDrive())
    {
        printf("\r\nDrive mounted\r\n");
        cd("/");
    }
    else
    {
        printf("\r\nNo SDCard Available.\r\n");
    }

    return 0;
}

BYTE loadFile(char *cwd, char *filename)
{
    char c;
    char fullName[13] = {0};

    if (!fileopen)
    {
        if (strcmp("/", cwd) == 0)
            sprintf(fullName, "%s", filename);
        else
            sprintf(fullName, "/%s/%s", cwd, filename);

        FRESULT res = f_open(&file, fullName, FA_OPEN_EXISTING | FA_READ);

        if (res != FR_OK)
        {
            printf("\r\nFile not found Error - %s\r\n", fullName);
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
        printf("\r\n%d bytes loaded.\r\n", f_size(&file));
    }

    return c;
}

int saveFile(char *cwd, char *filename, char *c)
{
    char fullName[256] = {0};

    if (!fileopen)
    {

        if (strcmp("/", cwd) == 0)
            sprintf(fullName, "%s", filename);
        else
            sprintf(fullName, "/%s/%s", cwd, filename);

        FRESULT res = f_open(&file, fullName, FA_CREATE_ALWAYS | FA_WRITE);

        if (res != FR_OK)
        {
            printf("\r\nFile not found Error.\r\n\r\n");
            return '~';
        }
        fileopen = 1;
    }

    UINT bw;

    FRESULT res = f_write(&file, c, 1, &bw);

    if (*c == '~')
    {
        f_close(&file);
        fileopen = 0;
        printf("\r\n%d bytes saved.\r\n", f_size(&file));
    }

    return *c;
}

int deleteFile(char *cwd, char *filename)
{
    char fullName[256] = {0};

    if (strcmp("/", cwd) == 0)
        sprintf(fullName, "%s", filename);
    else
        sprintf(fullName, "/%s/%s", cwd, filename);

    printf("\r\nDeleting: %s ...\r\n", fullName);
    FRESULT res = f_unlink(fullName);

    if (res == FR_OK)
        printf("Deleted.\r\n");
    else
        printf("Error - %d\r\n", res);

    return res;
}

void PrintDirectory(char *cwd)
{
    unsigned char i;
    unsigned char k;
    unsigned long lastStartCluster;
    int page = 0;

    printf("\r\nCurrent Directory: %s\r\n", cwd);
    scan_files(cwd);
    printf("\r\n");
}

FRESULT cd(char *directory)
{
    int res = f_chdir(directory);

    if (res == FR_OK)
        printf("Current Directory: %s\r\n", directory);
    else
        printf("Error - %d\r\n", res);

    return res;
}

FRESULT bload(char *cwd, uint32_t *filename, uint32_t *flen, uint32_t *startaddress)
{
    FIL file;
    char fullName[256] = {0};
    char string[256] = {0};
    uint8_t lenb = (uint8_t)((*flen >> 16) & 0xff);
    uintptr_t ptr = (uintptr_t)*filename;
    volatile char *buf = (char *)ptr;

    for (int i = 0; i < lenb; i++)
    {
        string[i] = *buf++;
    }

    if (strcmp("/", cwd) == 0)
        sprintf(fullName, "%s", string);
    else
        sprintf(fullName, "/%s/%s", cwd, string);


    FRESULT res = f_open(&file, fullName, FA_OPEN_EXISTING | FA_READ);
    if (res != FR_OK)
    {
        printf("\r\n%s - not found - %d\r\n", fullName, res);
        return res;
    }
    char buffer[512];
    UINT n;

    uint16_t *mem = (uint16_t *)*startaddress;


    printf("\r\nStart: 0x%lx",*startaddress);

    printf("\r\n");
    res = f_read(&file, buffer, 512, &n);
    while (n > 0)
    {

        for (int i = 0; i < (n - 1); i = i + 2)
        {

            uint16_t result = (((uint16_t)(buffer[i] & 0xFF) << 8) | (buffer[i + 1] & 0xFF) & 0xffff);

            *mem++ = result;
        }

        res = f_read(&file, buffer, 512, &n);
        if (res != FR_OK)
        {
            printf("Error - %d\r\n", res);
            return res;
        }

        printf(".");
    }
    f_close(&file);
    printf("\r\n");
    return 1;
}

int blsave(char *cwd, uint32_t *filename, uint32_t *flen, uint32_t *startaddress, uint32_t *endaddress)
{
    FIL file;
    char fullName[256] = {0};
    char string[256] = {0};
    uint8_t lenb = (uint8_t)((*flen >> 16) & 0xff);
    uintptr_t ptr = (uintptr_t)*filename;
    volatile char *buf = (char *)ptr;

    uintptr_t start_ptr = (uintptr_t)*startaddress;

    printf("\r\nStart: 0x%lX End: 0x%lX\r\n", *startaddress, *endaddress);



    for (int i = 0; i < lenb; i++)
    {
        string[i] = *buf++;
    }

    if (strcmp("/", cwd) == 0)
        sprintf(fullName, "%s", string);
    else
        sprintf(fullName, "/%s/%s", cwd, string);

    printf("\r\nFilename: %s\r\n", fullName);

    FRESULT res = f_open(&file, fullName, FA_CREATE_ALWAYS | FA_WRITE);

    if (res != FR_OK)
    {
        printf("\r\nFile not found Error.\r\n\r\n");
        return res;
    }

    uint32_t programlen = *endaddress - *startaddress;

    UINT bw;

    res = f_write(&file, start_ptr, programlen, &bw);
    if (res != FR_OK)
    {
        printf("Error - %d\r\n", res);
        return res;
    }

    f_close(&file);
    printf("\r\n");

    return bw;
}
