#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "fat_compat.h"

#define TESTDIR "/"

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



void PrintDirectory()
{
	unsigned char i;
	unsigned char k;
	unsigned long lastStartCluster;
	int page = 0;

	ChangeDirectoryName(TESTDIR);

	ScanDirectory(SCAN_INIT, "*", SCAN_DIR | SCAN_LFN);
	printf("\r\nDIR: %s\r\n", TESTDIR);
	while (1)
	{
		for (i = 0; i < nDirEntries; i++)
		{
			k = sort_table[i];
			printf("%c %s\t%s\t%lu bytes\r\n", i == iSelectedEntry ? '*' : ' ', DirEntries[k].fname, dateTimeStamp(DirEntries[k]), DirEntries[k].fsize);
		}
		lastStartCluster = DirEntries[0].fclust;
		if (nDirEntries == 8)
		{
			iSelectedEntry = MAXDIRENTRIES - 1;
			ScanDirectory(SCAN_NEXT_PAGE, "*", SCAN_DIR | SCAN_LFN);
			if (DirEntries[0].fclust == lastStartCluster)
				break;
			page++;
		}
		else
		{
			break;
		}
	}

	printf("\r\nEnd of Listing.\r\n");
}


void dump(unsigned char *buf)
{
	for (int i = 0; i < 512; i++)
	{
		if (i % 16 == 0)
		{
			printf(" ");
			for (int j = 0; j < 16; j++)
			{
				if (buf[i - 16 + j] > 32 && buf[i - 16 + j] < 128)
					printf("%c", buf[i - 16 + j]);
				else
					printf(" ");
			}
			printf("\r\n");
		}
		printf("%02x ", buf[i]);
	}
	printf("\r\n");
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
