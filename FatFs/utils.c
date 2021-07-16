#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "fat_compat.h"

//#define TESTDIR "/"

extern FILINFO DirEntries[MAXDIRENTRIES];
extern unsigned char sort_table[MAXDIRENTRIES];
extern unsigned char nDirEntries;
extern unsigned char iSelectedEntry;

char * dateTimeStamp(FILINFO file) {

	char *time;

	int year = 1980 + (file.fdate >> 9);
	int month = (file.fdate >> 5) & 0xf;
	int day = file.fdate & 0x1f;

	int hour = file.ftime >> 11;
	int min = (file.ftime >> 5) & 0x2f;
	int sec = file.fdate & 0x1f;

	sprintf(time,"%02d/%02d/%04d %02d:%02d:%02d", day, month, year,hour, min, sec);

	return time;
}


FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;

    res = f_opendir(&dir, path);                       /* Open the directory */

	if (res != FR_OK)
		return res;
	
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                //res = scan_files(path);                    /* Enter the directory */
                //if (res != FR_OK) break;
				printf("DIR %s\t%s\r\n", fno.fname, dateTimeStamp(fno));
                path[i] = 0;
            } else {                                       /* It is a file. */
                printf("%s\t%s\t%lu bytes\r\n", fno.fname, dateTimeStamp(fno), fno.fsize);
            }
        }
        f_closedir(&dir);
    }

    return res;
}



unsigned char bin2bcd(unsigned char in) {
  return 16*(in/10) + (in % 10);
}

unsigned char bcd2bin(unsigned char in) {
  return 10*(in >> 4) + (in & 0x0f);
}

 int _strnicmp(const char *s1, const char *s2, size_t n)
{
  char c1, c2;
  int v;

  do
    {
    c1 = *s1++;
    c2 = *s2++;
    if (!c1) break;
    v = (unsigned int)tolower(c1) - (unsigned int)tolower(c2);
    }
  while (v == 0 && --n > 0);

  return v;
}

void hexdump(void *data, uint16_t size, uint16_t offset) {
  uint8_t i, b2c;
  uint16_t n=0;
  char *ptr = data;

  if(!size) return;

  while(size>0) {
    iprintf("%04x: ", n + offset);

    b2c = (size>16)?16:size;
    for(i=0;i<b2c;i++)      iprintf("%02x ", 0xff&ptr[i]);
    iprintf("  ");
    for(i=0;i<(16-b2c);i++) iprintf("   ");
    for(i=0;i<b2c;i++)      iprintf("%c", isprint(ptr[i])?ptr[i]:'.');
    iprintf("\n");
    ptr  += b2c;
    size -= b2c;
    n    += b2c;
  }
}
