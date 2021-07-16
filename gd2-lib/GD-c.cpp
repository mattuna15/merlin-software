#include <stdint.h>
#include "GD-c.h"
#include <stdio.h>
#include "GD2.h"



void gd_begin()
{

    printf("\r\nChecking for Gameduino\r\n");

    GD.begin(0);

    byte r = GD.rd(REG_ID);

    if (r != 0x7c)
        exit(1);

    printf("\r\nGameduino found with ident: %0X\r\n", r);

    uint16_t err = GD.rd16(REG_CMD_READ);
    if (err == 0xfff)
    {
        printf("\r\nAlert %0x\r\n", err);
        GD.alert();
        exit(1);
    }
    //LOAD_ASSETS();

    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.swap();

    printf("\r\nInitialised Gameduino\r\n");
}

void gd_clear()
{
    GD.Clear();
}

void gd_clearColor(uint32_t *color)
{
    GD.ClearColorRGB(*color);
}

void gd_swap()
{
    GD.swap();
}

uint32_t gd_rand(uint32_t *seed)
{
    return GD.random(*seed);
}

void gd_line(uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2, uint32_t *size,
             uint32_t *color, uint32_t *begin)
{

    int lineWidth = 16 * *size;

    if (*begin == 1)
        GD.Begin(LINES);

    GD.LineWidth(lineWidth);
    GD.ColorRGB(*color);
    GD.VertexFormat(0);

    GD.Vertex2f(*x1, *y1);
    GD.Vertex2f(*x2, *y2);
}

void gd_text(uint32_t *x, uint32_t *y, uint32_t *font, uint32_t *color, uint32_t *text, uint32_t *len)
{

    char string[256] = {0};
    uint8_t lenb = (uint8_t)((*len >> 16) & 0xff);
    uintptr_t ptr = (uintptr_t)*text;
    volatile char *buf = (char *)ptr;

    for (int i = 0; i < lenb; i++)
    {
        string[i] = *buf++;
    }

    GD.VertexFormat(0);
    GD.ColorRGB(*color);

    if (*font == 0 || *font < 16 || *font > 31)
        *font = 18;

    GD.cmd_text(*x, *y, *font, 0, string);
}

void gd_plot(uint32_t *x, uint32_t *y, uint32_t *color, uint32_t *size, uint32_t *begin)
{

    int pointSize = 16 * *size;

    if (*begin == 1)
        GD.Begin(POINTS);

    GD.PointSize(pointSize);
    GD.ColorRGB(*color);
    GD.VertexFormat(0);

    GD.Vertex2f(*x, *y);
}

/* Bitmaps */

void gd_load_bitmap(uint32_t *pointer, uint32_t *count, uint32_t *asset_end ) {

    uint8_t *data = (uint8_t *)pointer;
    GD.copy(data, *count) ;
    GD.loadptr = *asset_end;

}

void gd_load_bitmapfile(uint32_t *filename, uint32_t *flen) {

    char string[256] = {0};
    uint8_t lenb = (uint8_t)((*flen >> 16) & 0xff);
    uintptr_t ptr = (uintptr_t)*filename;
    volatile char *buf = (char *)ptr;

    for (int i = 0; i < lenb; i++)
    {
        string[i] = *buf++;
    }

    GD.safeload(string);

}

void gd_draw_bitmap(uint32_t *x, uint32_t *y, uint32_t *size, uint32_t *handle, 
                        uint32_t *cell, uint32_t *blendsrc, uint32_t *blenddst ) {


  GD.Begin(BITMAPS);
  GD.BlendFunc(*blendsrc, *blenddst);
  GD.BitmapHandle(*handle);
  //GD.BitmapSize(NEAREST, BORDER, BORDER, *size, *size);
  //GD.BitmapLayout(ARGB4, 2 * *size, *size);

  GD.VertexFormat(3);
  GD.Cell(*cell);

  GD.Vertex2f(*x * *size * 8, *y * *size * 8);

}