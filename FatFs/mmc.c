/*
Copyright 2005, 2006, 2007 Dennis van Weeren
Copyright 2008, 2009 Jakub Bednarski

This file is part of Minimig

Minimig is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

Minimig is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// --== based on the work by Dennis van Weeren and Jan Derogee ==--
// 2008-10-03 - adaptation for ARM controller
// 2009-07-23 - clean-up and some optimizations
// 2009-11-22 - multiple sector read implemented

// FIXME - get capacity from SD card

//1GB:
//CSD:
//0000: 00 7f 00 32 5b 59 83 bc f6 db ff 9f 96 40 00 93   ...2[Y.��.�.@.�
//CID:
//0000: 3e 00 00 34 38 32 44 00 00 73 2f 6f 93 00 c7 cd   >..482D..s/o�...

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "mmc.h"
#include "fat_compat.h"

// variables
static unsigned char crc;
static unsigned long timeout;
static unsigned char response;
static unsigned char CardType;

// internal functions
static void MMC_CRC(unsigned char c)  ;

/*
SDADDRESS EQU $F40022  ;LONG (32BIT)
SDADDRESS2 EQU $F40024
SDDATA    EQU $F40027  
SDCONTROL EQU $F40021
SDSTATUS  EQU $F40020*/

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b)))) // '!!' to make sure this returns 0 or 1

volatile WORD *sd_status = (WORD *)0xf40020;
volatile BYTE *sd_control = (BYTE *)0xf40021;

volatile BYTE *sd_data = (BYTE *)0xf40027;
volatile DWORD *sd_address = (DWORD *)0xf40022;

#define SD_ERROR 0
#define SD_DIN_ACK 3
#define SD_DATA_AVAIL 4
#define SD_BUSY 5

#define SD_DIN_VALID 0
#define SD_DOUT_ACK 1
#define SD_READ_EN 2
#define SD_WRITE_EN 3
#define SD_MUL_READ_EN 4
#define SD_MUL_WRITE_EN 5

#define CARDTYPE_NONE 0
#define CARDTYPE_MMC 1
#define CARDTYPE_SD 2
#define CARDTYPE_SDHC 3

  unsigned char MMC_CheckCard()
{
    // check for removal of card
    if ((CardType != CARDTYPE_NONE))
    {
        CardType = CARDTYPE_NONE;
        return 0;
    }
    return 1;
}

static   char check_card()
{

    MMC_CheckCard();
    // check of card has been removed and try to re-initialize it
    if (CardType == CARDTYPE_NONE)
    {
        if (!MMC_Init())
            return 0;
    }
    return 1;
}

// init memory card
unsigned char MMC_Init(void)
{
    WORD status;

    status = *sd_status >> 8;
    CardType = status >> 6;

    if (BIT_CHECK(status, SD_ERROR) == true)
    {
        return CARDTYPE_NONE;
    }

    return CardType;
}

void EnableReadCard(int multi)
{

    WORD status = *sd_status >> 8;

    while (BIT_CHECK(status, SD_BUSY) == true)
    {
       // printf(":");
        status = *sd_status >> 8;
    }

    if (multi)
        BIT_SET(*sd_control, SD_MUL_READ_EN);
    else
        BIT_SET(*sd_control, SD_READ_EN);
}

void DisableReadCard(int multi)
{

    if (multi)
        BIT_CLEAR(*sd_control, SD_MUL_READ_EN);
    else
        BIT_CLEAR(*sd_control, SD_READ_EN);
}

// Read single 512-byte block
  unsigned char MMC_Read(unsigned long lba, unsigned char *pReadBuffer)
{
    // if pReadBuffer is NULL then use direct to the FPGA transfer mode (FPGA2 asserted)

    // check of card has been removed and try to re-initialize it
    if (!check_card())
        return 0;

    unsigned long i;
    unsigned char *p;

    if (CardType != CARDTYPE_SDHC) // SDHC cards are addressed in sectors not bytes
        lba = lba << 9;            // otherwise convert sector adddress to byte address

    WORD status = *sd_status >> 8;

    // printf("\r\r\nInitial status: %0X\r\n", status);
    if (status != 0xc0)
    {

        *sd_control = 0x0006;

        status = *sd_status >> 8;
        while (BIT_CHECK(status, SD_DATA_AVAIL) == true)
        {
            // printf("\r\nInitial status: %0X\r\n", status);
            status = *sd_status >> 8;
        }

        *sd_control = 0x0000;
    }

    *sd_address = lba;

    EnableReadCard(0);

    for (int datacounter = 0; datacounter < 512; datacounter++)
    {

        status = *sd_status >> 8;
        while (BIT_CHECK(status, SD_DATA_AVAIL) == false)
        {
            // printf("\r\ndata status: %0X\r\n", status);
            // printf("-");
            status = *sd_status >> 8;
        }

        BYTE temp = *sd_data;
        BIT_SET(*sd_control, SD_DOUT_ACK);
        pReadBuffer[datacounter] = temp;
        //   printf(".");

        status = *sd_status >> 8;
        while (BIT_CHECK(status, SD_DATA_AVAIL) == true)
        {
            status = *sd_status >> 8;
        }

        BIT_CLEAR(*sd_control, SD_DOUT_ACK);

        status = *sd_status >> 8;
        if (BIT_CHECK(status, SD_ERROR) == true)
        {
            printf("\r\nError!\r\n");
            BIT_CLEAR(*sd_control, SD_READ_EN);
            BIT_CLEAR(*sd_control, SD_DOUT_ACK);
            return 0;
        }
    }

    DisableReadCard(0);
    return (1);
}

// read multiple 512-byte blocks
unsigned char MMC_ReadMultiple(unsigned long lba, unsigned char *pReadBuffer, unsigned long nBlockCount)
{

    // check of card has been removed and try to re-initialize it
    if (!check_card())
        return 0;

    unsigned long i;
    unsigned char *p;

    if (CardType != CARDTYPE_SDHC) // SDHC cards are addressed in sectors not bytes
        lba = lba << 9;            // otherwise convert sector adddress to byte address

    WORD status = *sd_status >> 8;

    // printf("\r\nInitial status: %0X\r\n", status);
    if (status != 0xc0)
    {

        *sd_control = 0x0006;

        status = *sd_status >> 8;
        while (BIT_CHECK(status, SD_DATA_AVAIL) == true)
        {
            // printf("\r\nInitial status: %0X\r\n", status);
            status = *sd_status >> 8;
        }

        *sd_control = 0x0000;
    }

    *sd_address = lba;

    EnableReadCard(1);

    while (nBlockCount--)
    {
        for (int datacounter = 0; datacounter < 512; datacounter++)
        {

            status = *sd_status >> 8;
            while (BIT_CHECK(status, SD_DATA_AVAIL) == false)
            {
                // printf("\r\ndata status: %0X\r\n", status);
                // printf("-");
                status = *sd_status >> 8;
            }

            BYTE temp = *sd_data;
            BIT_SET(*sd_control, SD_DOUT_ACK);
            pReadBuffer[datacounter] = temp;
            //   printf(".");

            status = *sd_status >> 8;
            while (BIT_CHECK(status, SD_DATA_AVAIL) == true)
            {
                status = *sd_status >> 8;
            }

            BIT_CLEAR(*sd_control, SD_DOUT_ACK);

            status = *sd_status >> 8;
            if (BIT_CHECK(status, SD_ERROR) == true)
            {
                printf("\r\nError!\r\n");
                BIT_CLEAR(*sd_control, SD_READ_EN);
                BIT_CLEAR(*sd_control, SD_DOUT_ACK);
                return 0;
            }
        }
    }

    DisableReadCard(1);
    return (1);
}

// write 512-byte block
unsigned char MMC_Write(unsigned long lba, const unsigned char *pWriteBuffer)
{
    unsigned long i;

    // check of card has been removed and try to re-initialize it
    if (!check_card())
        return 0;

    if (CardType != CARDTYPE_SDHC) // SDHC cards are addressed in sectors not bytes
        lba = lba << 9;            // otherwise convert sector adddress to byte address

    WORD status = *sd_status >> 8;

    *sd_address = lba;

    status = *sd_status >> 8;
    /* Send data bytes to the card */
    while (BIT_CHECK(status, SD_BUSY) == true)
    {
        //wait
        status = *sd_status >> 8;
    }

    BIT_SET(*sd_control, SD_WRITE_EN);
    int wc = 512;

    while (wc)
    {

        status = *sd_status >> 8;
        if (BIT_CHECK(status, SD_ERROR) == true)
        {
            printf("\r\nError!\r\n");
            BIT_CLEAR(*sd_control, SD_READ_EN);
            BIT_CLEAR(*sd_control, SD_DOUT_ACK);
            return 0;
        }

        *sd_data = *pWriteBuffer++;

        BIT_SET(*sd_control, SD_DIN_VALID);

        status = *sd_status >> 8;
        /* Send data bytes to the card */

        while (BIT_CHECK(status, SD_DIN_ACK) == false)
        {
            //wait
            status = *sd_status >> 8;
        }

        BIT_CLEAR(*sd_control, SD_DIN_VALID);
    //    printf(".");

        wc--;
    }

    // Finalize write process
   // printf("\r\nDisabled\r\n");
    BIT_CLEAR(*sd_control, SD_WRITE_EN);

    return 1;
}

// MMC CRC calc
static   void MMC_CRC(unsigned char c)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        crc <<= 1;
        if (c & 0x80)
            crc ^= 0x09;
        if (crc & 0x80)
            crc ^= 0x09;
        c <<= 1;
    }
}

unsigned char MMC_IsSDHC(void)
{
    return (CardType == CARDTYPE_SDHC);
}
