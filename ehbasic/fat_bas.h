#ifndef FAT_BAS
#define FAT_BAS	86631	/* Revision ID */

#include <stdint.h>
#include "../FatFs/ff.h"

BYTE loadFile(char *filename);
int saveFile(char *filename, char *c);
int deleteFile(char *filename);

#endif