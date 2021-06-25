#ifndef FAT_BAS
#define FAT_BAS	86631	/* Revision ID */

#include <stdint.h>
#include "../FatFs/ff.h"

FRESULT loadFile();
FRESULT saveFile();
FRESULT deleteFile();

#endif