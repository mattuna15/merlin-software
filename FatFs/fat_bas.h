#ifndef FAT_BAS
#define FAT_BAS	86631	/* Revision ID */

#include <stdint.h>
#include "ff.h"

int initDrive(void);
BYTE loadFile(char* cwd,char *filename);
int saveFile(char* cwd,char *filename, char *c);
int deleteFile(char* cwd,char *filename);
FRESULT cd(char *directory);
void PrintDirectory(char* cwd);

#endif