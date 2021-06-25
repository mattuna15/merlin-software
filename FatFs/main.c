#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "fat_compat.h"

#define TESTDIR "/"

extern FILINFO DirEntries[MAXDIRENTRIES];
extern unsigned char sort_table[MAXDIRENTRIES];
extern unsigned char nDirEntries;
extern unsigned char iSelectedEntry;

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

////////////////////////////////////////////////////////////////////

void FileReadTest(char *fname)
{
	FIL file;
	char buf[512];

	if (FileOpenCompat(&file, fname, FA_READ) == FR_OK)
	{
		FileReadBlock(&file, buf);

		int fsize = f_size(&file);
		printf("\r\nFilesize: %d\r\n", fsize);

		for (int i = 0; i < fsize; i++)
		{
			printf("%c", buf[i]);
		}
		printf("\r\n");

		f_close(&file);
	}
	else
	{
		printf("Error opening %s\r\n", fname);
	}
}

void ScanDirectoryTest()
{
	unsigned char i;
	unsigned char k;
	unsigned long lastStartCluster;
	int page = 0;

	ChangeDirectoryName(TESTDIR);

	ScanDirectory(SCAN_INIT, "*", SCAN_DIR | SCAN_LFN);
	printf("Number of entries = %d\r\n", nDirEntries);
	while (1)
	{
		for (i = 0; i < nDirEntries; i++)
		{
			k = sort_table[i];
			printf("%c %s %lu", i == iSelectedEntry ? '*' : ' ', DirEntries[k].fname, DirEntries[k].fsize);
			printf("\r\n");
		}
		lastStartCluster = DirEntries[0].fclust;
		if (nDirEntries == 8)
		{
			iSelectedEntry = MAXDIRENTRIES - 1;
			printf("Next Page\r\n");
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
}

void FileWriteTest(char *name) {
	FIL file;
//	unsigned char buf[512];
	char *text = "All done";

	// strcpy(buf,text);

	// buf[sizeof(text)] = '\0';

	FRESULT open = FileOpenCompat(&file, name, FA_OPEN_APPEND | FA_WRITE);

	if (open != FR_OK)
	{
		printf("\r\nOpen failed: %d\r\n",open);
	}

	UINT bw;
	FRESULT write = f_write(&file, text, strlen(text), &bw);

	if (write != FR_OK)
		printf("\r\nWrite failed: %d\r\n",write);
	else
		printf("\r\n Bytes written %d, Result: %d\r\n",bw,write);

	f_close(&file);
}



int main()
{

	printf("\r\n");
	FindDrive();
	ScanDirectoryTest();
	FileReadTest("MESSAG~1TXT");

	FileWriteTest("NEW3    TXT");
	ScanDirectoryTest();
	FileReadTest("NEW3    TXT");

	print("done\r\n\r\n");

}