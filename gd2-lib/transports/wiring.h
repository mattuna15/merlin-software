#ifndef _WIRING_H_INCLUDED
#define _WIRING_H_INCLUDED

#include "../GD2.h"
#include <stdint.h>
#include <string.h>

#define CS 0

uint8_t volatile *spi_ctl = (uint8_t volatile *)0xf40009;
uint8_t volatile *spi_data_in = (uint8_t volatile *)0xf4000b;
uint8_t volatile *spi_data_out = (uint8_t volatile *)0xf4000d;
byte lowByte(uint16_t input)
{

  return input & 0xff;
}

byte highByte(uint16_t input)
{

  return (input >> 8) & 0xff;
}

class GDTransport
{
private:
  byte cs;
  byte model;

public:
  void begin0(int _cs = CS)
  {

    cs = _cs;

    SPI.begin();

    hostcmd(0x42); // SLEEP

    hostcmd(0x00);
    hostcmd(0x68);
  }
  void begin1()
  {
    // for (int i = 0; i < 100; i++) { Serial.println(__rd16(0xc0000UL), HEX); delay(10); }
#if 1
    delay(320);
#else
    while (__rd16(0xc0000UL) == 0xffff)
      ;
#endif
    printf("\r\nBegin loop\r\n");
    while ((__rd16(0xc0000UL) & 0xff) != 0x08 && (__rd16(0xc0000UL) & 0xff) != 0x15)
    {
      // printf("result: %0X\r\n", (__rd16(0xc0000UL) & 0xff) );
    }

    // So that FT800,801      FT810-3   FT815,6
    // model       0            1         2
    switch (__rd16(0x0c0000UL) >> 8)
    {
    case 0x00:
    case 0x01:
      ft8xx_model = 0;
      break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
      ft8xx_model = 1;
      break;
    case 0x15:
    case 0x16:
      ft8xx_model = 2;
      break;
    default:
      ft8xx_model = 2;
      break;
    }
    //REPORT(ft8xx_model);
    // uint16_t x = __rd16(0x0c0000UL);
    //REPORT(x);

    wp = 0;
    freespace = 4096 - 4;

    printf("\nbegin finished - stream starting \n");

    stream();
  }

  void external_crystal()
  {
    __end();
    hostcmd(0x44);
  }

  void cmd32(uint32_t x)
  {
    if (freespace < 4)
    {
      getfree(4);
    }
    wp += 4;
    freespace -= 4;

    union
    {
      uint32_t c;
      uint8_t b[4];
    };

    c = x;
    printf("cmd32: %0lX, freespace: %0d, wp: %0d\r\n", c, freespace, wp);
    printf("%X %X %X %X\r\n", b[3], b[2], b[1], b[0]);
    SPI.transfer(b[3]);
    SPI.transfer(b[2]);
    SPI.transfer(b[1]);
    SPI.transfer(b[0]);
  }
  void cmdbyte(byte x)
  {
    if (freespace == 0)
    {
      getfree(1);
    }
    wp++;
    freespace--;
    SPI.transfer(x);
  }
  void cmd_n(byte *s, uint16_t n)
  {
    if (freespace < n)
    {
      getfree(n);
    }
    wp += n;
    freespace -= n;

    while (n > 8)
    {
      n -= 8;
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
    }
    while (n--)
      SPI.transfer(*s++);
  }

  void flush()
  {
    delay(1);
    getfree(0);
  }
  void coprocsssor_recovery(void)
  {
    __end();
    if (ft8xx_model >= 2)
      for (byte i = 0; i < 128; i += 2)
        __wr16(i, __rd16(0x309800UL + i));

    __wr16(REG_CPURESET, 1);
    __wr16(REG_CMD_WRITE, 0);
    __wr16(REG_CMD_READ, 0);
    wp = 0;
    __wr16(REG_CPURESET, 0);
    stream();
  }
  uint16_t rp()
  {
    uint16_t r = __rd16(REG_CMD_READ);
    if (r == 0xfff)
      printf("\r\nAlert %0x\r\n", r);

    // GD.alert();
    return r;
  }
  void finish()
  {
    wp &= 0xffc;
    __end();
    __wr16(REG_CMD_WRITE, wp);
    while (rp() != wp)
    {
      delay(1);
    }

    stream();
  }

  byte rd(uint32_t addr)
  {
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0); // dummy
    byte r = SPI.transfer(0);
    stream();
    return r;
  }

  void wr(uint32_t addr, byte v)
  {
    __end(); // stop streaming
    __wstart(addr);
    SPI.transfer(v);
    stream();
  }

  uint16_t rd16(uint32_t addr)
  {
    uint16_t r = 0;
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);
    r = SPI.transfer(0);
    r |= (SPI.transfer(0) << 8);
    stream();
    return r;
  }

  void wr16(uint32_t addr, uint32_t v)
  {
    __end(); // stop streaming
    __wstart(addr);
    SPI.transfer(v);
    SPI.transfer(v >> 8);
    stream();
  }

  uint32_t rd32(uint32_t addr)
  {
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);
    uint32_t ftData32 = 0x00000000;
    uint32_t tempData32 = 0x00000000;
       
    tempData32 = SPI.transfer( 0x00 );                                      // Read low byte of data first
    ftData32 = ftData32 | tempData32;
     
    tempData32 = SPI.transfer( 0x00 );
    tempData32 = ((tempData32 << 8) & 0x0000FF00);
    ftData32 = ftData32 | tempData32;

    tempData32 = SPI.transfer( 0x00 );
    tempData32 = ((tempData32 << 16) & 0x00FF0000);
    ftData32 = ftData32 | tempData32;    
    
    tempData32 = SPI.transfer( 0x00 );                                      // Read high byte of data last
    tempData32 = ((tempData32 << 24) & 0xFF000000);
    ftData32 = ftData32 | tempData32;  

    stream();
    return ftData32;
  }
  void rd_n(byte *dst, uint32_t addr, uint16_t n)
  {
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);
    while (n--)
      *dst++ = SPI.transfer(0);
    stream();
  }

  void wr_n(uint32_t addr, byte *src, uint16_t n)
  {
    __end(); // stop streaming
    __wstart(addr);

    while (n--)
      SPI.transfer(*src++);

    stream();
  }

  void wr32(uint32_t addr, unsigned long v)
  {
    __end(); // stop streaming
    __wstart(addr);
    SPI.transfer(v);
    SPI.transfer(v >> 8);
    SPI.transfer(v >> 16);
    SPI.transfer(v >> 24);
    stream();
  }

  uint32_t getwp(void)
  {
    return RAM_CMD + (wp & 0xffc);
  }

  void bulk(uint32_t addr)
  {
    __end(); // stop streaming
    __start(addr);
  }
  void resume(void)
  {
    stream();
  }

  void __start(uint32_t addr) // start an SPI transaction to addr
  {

    BIT_SET(*spi_ctl, GPU_CS);
    SPI.transfer(addr >> 16);
    SPI.transfer(highByte(addr));
    SPI.transfer(lowByte(addr));
  }

  void __wstart(uint32_t addr) // start an SPI write transaction to addr
  {

    // printf("\r\n*****W Start Addr: %lX", addr);

    // byte b = 0x80 | (addr >> 16);
    // printf("\r\n1: %0X\r\n", b);
    // b = highByte(addr);
    // printf("2: %0X\r\n", b);
    // b = lowByte(addr);
    // printf("3: %0X\r\n",b);

    BIT_SET(*spi_ctl, GPU_CS);
    SPI.transfer((addr >> 16) | 0x80);
    SPI.transfer(highByte(addr));
    SPI.transfer(lowByte(addr));
  }

  void __end() // end the SPI transaction
  {
    BIT_CLEAR(*spi_ctl, GPU_CS);
  }

  void stop() // end the SPI transaction
  {
    wp &= 0xffc;
    __end();
    __wr16(REG_CMD_WRITE, wp);
    // while (__rd16(REG_CMD_READ) != wp) ;
  }

  void capture_error_message(void)
  {
    __end();
    if (ft8xx_model >= 2)
      for (byte i = 0; i < 128; i += 2)
        __wr16(i, __rd16(0x309800UL + i));
  }

  void stream(void)
  {
    __end();
    // printf("Stream*********************\r\n");
    __wstart(RAM_CMD + (wp & 0xfff));
  }

  unsigned int __rd16(uint32_t addr)
  {
    uint16_t r = 0;
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);
    r = SPI.transfer(0);
    r |= (SPI.transfer(0) << 8);
    stream();
    return r;
  }

  void __wr16(uint32_t addr, unsigned int v)
  {
    __wstart(addr);
    SPI.transfer(lowByte(v));
    SPI.transfer(highByte(v));
    __end();
  }

  void hostcmd(byte a)
  {
    BIT_SET(*spi_ctl, GPU_CS);
    SPI.transfer(a);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    BIT_CLEAR(*spi_ctl, GPU_CS);
  }

  void getfree(uint16_t n)
  {
    wp &= 0xfff;
    __end();
    __wr16(REG_CMD_WRITE, wp & 0xffc);
    do
    {
      uint16_t fullness = (wp - rp()) & 4095;
      freespace = (4096 - 4) - fullness;
    } while (freespace < n);
    stream();
  }
  void daz_rd(uint8_t *s, size_t n)
  {
    __end();
    BIT_SET(*spi_ctl, DAZ_CS);
    memset(s, 0xff, n);
    SPI.transfer((byte *)s, n);
    BIT_CLEAR(*spi_ctl, DAZ_CS);
    resume();
  }

  byte streaming;
  uint16_t wp;
  uint16_t freespace;
};

#endif