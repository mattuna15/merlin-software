/*!
 *  @file Adafruit_FRAM_SPI.h
 *
 *  This is a library for the Adafruit SPI FRAM breakout.
 *
 *  Designed specifically to work with the Adafruit SPI FRAM breakout.
 *
 *  Pick one up today in the adafruit shop!
 *  ------> https://www.adafruit.com/product/1897
 *
 *  These module use SPI to communicate, 4 pins are required to interface.
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  K.Townsend (Adafruit Industries)
 *
 *  BSD license, all text above must be included in any redistribution
 */
#ifndef _ADAFRUIT_FRAM_SPI_H_
#define _ADAFRUIT_FRAM_SPI_H_

#include <stdint.h>
#include <stdio.h>

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b)))) // '!!' to make sure this returns 0 or 1

#define FRAM1_CS 0
#define VALID_OUT 3
#define READY 5

#define byte uint8_t

/** Operation Codes **/
typedef enum opcodes_e
{
  OPCODE_WREN = 0b0110,    /* Write Enable Latch */
  OPCODE_WRDI = 0b0100,    /* Reset Write Enable Latch */
  OPCODE_RDSR = 0b0101,    /* Read Status Register */
  OPCODE_WRSR = 0b0001,    /* Write Status Register */
  OPCODE_READ = 0b0011,    /* Read Memory */
  OPCODE_WRITE = 0b0010,   /* Write Memory */
  OPCODE_RDID = 0b10011111 /* Read Device ID */
} opcodes_t;

class ASPI_t
{

  uint8_t volatile *spi_ctl = (uint8_t volatile *)0xf40039;
  uint8_t volatile *spi_data_in = (uint8_t volatile *)0xf4003b;
  uint8_t volatile *spi_data_out = (uint8_t volatile *)0xf4003d;

public:
  bool begin(void)
  {
    BIT_CLEAR(*spi_ctl, FRAM1_CS);
    return 1;
  }

  void setFram1On()
  {
    BIT_SET(*spi_ctl, FRAM1_CS);
  }
  void setFram1Off()
  {
    BIT_CLEAR(*spi_ctl, FRAM1_CS);
  }

  void delay(int ms)
  {

    for (int i = 0; i < ms; i++)
    {
      asm("nop");
    }
  }

  byte transfer(byte x)
  {
    byte r = 0;

    //printf("\r\ns:%0X ", x);

    while (!BIT_CHECK(*spi_ctl, READY))
    {
    }

    *spi_data_in = x;

    BIT_SET(*spi_ctl, VALID_OUT);
    BIT_CLEAR(*spi_ctl, VALID_OUT);

    while (!BIT_CHECK(*spi_ctl, READY))
    {
    }

    r = *spi_data_out;
    //printf("r:%0X\r\n", r);

    return r;
  }
  void transfer(byte *m, int s)
  {
    while (s--)
    {
      *m = transfer(*m);
      m++;
    }
  }

  int write(uint8_t *buffer, size_t len,
            uint8_t *prefix_buffer, size_t prefix_len)
  {
    setFram1On();
    // do the writing
    for (size_t i = 0; i < prefix_len; i++)
    {
      transfer(prefix_buffer[i]);
    }
    for (size_t i = 0; i < len; i++)
    {
      transfer(buffer[i]);
    }
    setFram1Off();

    return true;
  }

  int write(uint8_t *buffer, size_t len)
  {
    setFram1On();
    // do the writing
    for (size_t i = 0; i < len; i++)
    {
      transfer(buffer[i]);
    }
    setFram1Off();

    return true;
  }

  bool write_then_read(uint8_t *write_buffer,
                       size_t write_len, uint8_t *read_buffer,
                       size_t read_len, uint8_t sendvalue)
  {
    setFram1On();
    // do the writing
    for (size_t i = 0; i < write_len; i++)
    {
      transfer(write_buffer[i]);
    }

    // do the reading
    for (size_t i = 0; i < read_len; i++)
    {
      read_buffer[i] = transfer(sendvalue);
    }

    setFram1Off();

    return true;
  }
};
static class ASPI_t ASPI;
#define SPI ASPI

/*!
 *  @brief  Class that stores state and functions for interacting with
 *          FRAM SPI
 */
class Adafruit_FRAM_SPI
{
public:
  Adafruit_FRAM_SPI();

  bool begin(uint8_t nAddressSizeBytes = 2);
  void writeEnable(bool enable);
  void write8(uint32_t addr, uint8_t value);
  void write(uint32_t addr, uint8_t *values, size_t count);
  uint8_t read8(uint32_t addr);
  void read(uint32_t addr, uint8_t *values, size_t count);
  void getDeviceID(uint8_t *manufacturerID, uint16_t *productID);
  uint8_t getStatusRegister(void);
  void setStatusRegister(uint8_t value);
  void setAddressSize(uint8_t nAddressSize);

private:
  ASPI_t *spi_dev = &ASPI;
  uint8_t _nAddressSizeBytes;
};

#endif
