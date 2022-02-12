#ifndef FAT_BAS
#define FAT_BAS	86631	/* Revision ID */

#include <stdint.h>
#include "ff.h"

#ifdef __cplusplus
extern "C" {
#endif

int initDrive(void);
BYTE loadFile(char* cwd,char *filename);
int saveFile(char* cwd,char *filename, char *c);
int deleteFile(char* cwd,char *filename);
FRESULT cd(char *directory);
void PrintDirectory(char* cwd);

FRESULT cd(char *directory);
FRESULT bload(char* cwd,uint32_t *filename, uint32_t *flen, uint32_t *startaddress);
int blsave(char *cwd, uint32_t *filename, uint32_t *flen, uint32_t *startaddress, uint32_t *endaddress);

#ifdef __cplusplus
}
#endif


#endif 