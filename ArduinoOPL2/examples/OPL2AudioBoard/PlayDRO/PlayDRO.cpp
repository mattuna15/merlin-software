/**
 * This is an example sketch from the OPL2 library for Arduino. It plays a DRO audio file from SD card using the YM3812
 * audio chip.
 *
 * OPL2 board is connected as follows:
 *   Pin  8 - Reset
 *   Pin  9 - A0
 *   Pin 10 - Latch
 *   Pin 11 - Data
 *   Pin 13 - Shift
 *
 * Connect the SD card with Arduino SPI pins as usual and use pin 7 as CS.
 *
 * Refer to the wiki at https://github.com/DhrBaksteen/ArduinoOPL2/wiki/Connecting to learn how to connect your platform
 * of choice!
 *
 * By default this example will look for the phemopop.dro file in the root of the SD card. This file is found among the
 * files for this example. For more information about the DRO file format please visit
 * http://www.shikadi.net/moddingwiki/DRO_Format
 *
 * Code by Maarten Janssen (maarten@cheerful.nl) 2016-12-17
 * Song Phemo-pop! by Olli Niemitalo/Yehar 1996
 * Most recent version of the library can be found at my GitHub: https://github.com/DhrBaksteen/ArduinoOPL2
 */

#include <string>
#include <cstring>
#include <map>
#include <stdio.h>
#include "../../../../FatFs/fat_bas.h"
#include "../../../src/OPL3Duo.h"


unsigned long SwapBBBB(unsigned long i)
{
	asm volatile
	(
		"rol.w #8,%0\n\t"
		"swap %0\n\t"
		"rol.w #8,%0\n\t"
	: "=r" (i) /* out */
	: "r" (i) 
	: /* no clobber */
	);	
	return i;
}

unsigned int SwapBB(unsigned int i)
{
	asm volatile
	(
		"rol.w #8,%0\n\t"
	: "=r" (i) /* out */
	: "r" (i) 
	: /* no clobber */
	);	
	return i;
}

unsigned long SwapWW(unsigned long i)
{
	asm volatile
	(
		"swap %0\n\t"
	: "=r" (i) /* out */
	: "r" (i) 
	: /* no clobber */
	);	
	return i;
}

FIL droFile;

unsigned long offset = 0;
unsigned long songLength = 0;
unsigned long songDuration = 0;
byte codeShortDelay = 0;
byte codeLongDelay = 0;
byte registerMapLength = 0;
byte registerMap[256];

void loadDroSong(char *fileName);
int playDroSong();

OPL3Duo opl3Duo;

uint32_t *timer = (uint32_t *)0xf30030;

void delayMillis(int ms)
{
    uint32_t start = *timer;
    uint32_t current = *timer;
   // printf("\r\nStart %lu, time %d\r\n", start, ms);

	  while ((current-start) <= ms) {
      current = *timer;
      asm("nop");
    }
    //printf("\r\nFinished waiting\r\n");
}

void setup()
{

  printf("\r\nDRO Player\r\n");

	opl3Duo.begin();
	opl3Duo.setOPL3Enabled(false);

  printf("\r\nSound card ready, mounting drive\r\n");

  initDrive();

  //loadDroSong("phemopop.dro");
  std::string str = "/STRFOR.DRO";
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());

  loadDroSong(cstr);
}


int main()
{
  
  setup();

  unsigned long time = (unsigned long)*timer;

  while (songLength > 0)
  {
    time = (unsigned long)*timer;
    int wait = playDroSong();

    if (wait > 0)
    {
      // Take into account time that was spent on IO.
      unsigned long ioTime = (unsigned long)*timer - time;
      if (ioTime < wait)
      {
        delayMillis(wait - ioTime);
      }
    }

    songLength--;
  }

  opl3Duo.reset();

  f_close(&droFile);

}

void loadDroSong(char *fileName)
{
  FRESULT res;
  uint32_t buf;
  UINT *bytesRead;

  res = f_open(&droFile, fileName, FA_OPEN_EXISTING | FA_READ);

  if (res != FR_OK) {
    printf("\r\n%s Error code %d\r\n", fileName, res);
    exit(0);
  }

  f_lseek(&droFile, 12);
  f_read(&droFile, &buf, 4, bytesRead);

  songLength = SwapBBBB(buf);

  printf("\r\nSong length: %lu\r\n", songLength);

  f_read(&droFile, &buf, 4, bytesRead);

  //SwapBytes(buf, 4);
  songDuration = SwapBBBB(buf);
  printf("\r\nSong duration: %lu\r\n", songDuration);

  f_lseek(&droFile, 23);

  f_read(&droFile, &codeShortDelay, 1, bytesRead);
  f_read(&droFile, &codeLongDelay, 1, bytesRead);
  f_read(&droFile, &registerMapLength, 1, bytesRead);

  for (byte i = 0; i < registerMapLength; i++)
  {
    f_read(&droFile, &registerMap[i], 1, bytesRead);
  }
}

int playDroSong()
{
  byte code = 0;
  byte data = 0;
  UINT *bytesRead;

  f_read(&droFile, &code, 1, bytesRead);
  f_read(&droFile, &data, 1, bytesRead);

  if (code == codeShortDelay)
  {
    return data + 1;
  }
  else if (code == codeLongDelay)
  {
    int delay = data;
    f_read(&droFile, &data, 1, bytesRead);
    delay = (data << 8) + delay;
    return (delay + 1);
  }
  else if (code < 128)
  {
    opl3Duo.write(0, registerMap[code], data);
  }

  return 0;
}
