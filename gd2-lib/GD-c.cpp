#include <stdint.h>
#include "GD-c.h"
#include <stdio.h>
#include "GD2.h"
#include <stdlib.h>
#include <math.h>

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
    // LOAD_ASSETS();

    GD.ClearColorRGB(0x0);
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

void gd_seed()
{

    uint16_t *timer = (uint16_t *)0xf30032;

    printf("\r\ntimer: %d\r\n",*timer);

    srand(*timer);
}

uint16_t gd_rand(uint16_t *max)
{

    uint16_t r = 0;
    
    //while (r == 0) {
        r = rand() % *max;
    //}

    return r;
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

void gd_load_bitmap(uint32_t *pointer, uint32_t *count, uint32_t *asset_end)
{

    uint8_t *data = (uint8_t *)pointer;
    GD.copy(data, *count);
    GD.loadptr = *asset_end;
}

void gd_load_bitmapfile(uint32_t *filename, uint32_t *flen)
{

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
                    uint32_t *cell, uint32_t *blendsrc, uint32_t *blenddst)
{

    GD.Begin(BITMAPS);
    GD.BlendFunc(*blendsrc, *blenddst);
    GD.BitmapHandle(*handle);
    // GD.BitmapSize(NEAREST, BORDER, BORDER, *size, *size);
    // GD.BitmapLayout(ARGB4, 2 * *size, *size);

    GD.VertexFormat(3);
    GD.Cell(*cell);

    GD.Vertex2f(*x * *size * 8, *y * *size * 8);
}

void gd_mode(uint32_t *mode)
{

    SPI.setGPUOff();
    SPI.setDazOn();
    SPI.transfer(0x41);

    printf("\r\n** Mode %d Selected  **\r\n", (byte)*mode);
    SPI.transfer((byte)*mode);
    SPI.setDazOff();
    SPI.setGPUOn();
}

void game_start()
{

    GD.storage();
    GD.begin();

    GD.ClearColorRGB(0x0);
    GD.Clear();
}

int16_t curX = 0;
int16_t curY = 0;

union Vertex
{
    int8_t vertex8[4];
    uint16_t vertex16[2];
    uint32_t vertex32;
};

void beginLine(uint32_t *startPoint)
{

    union Vertex point;

    point.vertex32 = *startPoint;

    curX = point.vertex16[0];
    curY = point.vertex16[1];

    GD.Begin(LINES);
    GD.VertexFormat(0);
    GD.ColorRGB(0xFFFFFF);
    GD.BlendFunc(SRC_ALPHA, ONE);

}

void addPoint(uint32_t *nextPoint)
{

    union Vertex point;

    point.vertex32 = *nextPoint;

    int16_t prevX = curX;
    int16_t prevY = curY;

    int16_t diffX = point.vertex8[2] * point.vertex8[0];
    int16_t diffY = point.vertex8[3] * point.vertex8[0];

    int brightness = point.vertex8[1];
    if (brightness == 0)
        GD.ColorRGB(0x0);
    else
        GD.ColorRGB(0xFFFFFF);

    curX += diffX;
    curY += diffY;

    GD.ColorA(0xf0 + brightness); // Draw foreground vectors
    GD.LineWidth(5);
    GD.Vertex2f(prevX, prevY);
    GD.Vertex2f(curX, curY);
}

uint32_t polar(int16_t *r, uint16_t *th)
{

    uint16_t heading = (uint16_t)*th;
    int16_t velocity = (int16_t)*r;

    int16_t x = (int16_t)(-GD.rsin(velocity, heading));
    int16_t y = (int16_t)(GD.rcos(velocity, heading));

    uint32_t cart = y << 16;
    cart += x;

    return cart;
}


uint32_t polar_ship(int16_t *r, uint16_t *th, int16_t *old_r, uint16_t *old_th) {


    uint16_t heading = (uint16_t)*th;
    int16_t velocity = (int16_t)*r;
    uint16_t old_heading = (uint16_t)*old_th;
    int16_t old_velocity = (int16_t)*old_r;

    int16_t x = (int16_t)(-GD.rsin(velocity, heading));
    int16_t y = (int16_t)(GD.rcos(velocity, heading));

    int16_t oldx = (int16_t)(-GD.rsin(old_velocity, old_heading));
    int16_t oldy = (int16_t)(GD.rcos(old_velocity, old_heading));

    uint32_t cart = (y + oldy) << 16;
    cart += (x + oldx);

    return cart;
}


void bullet(uint32_t *startPoint)
{

    union Vertex point;

    point.vertex32 = *startPoint;

    curX = point.vertex16[0];
    curY = point.vertex16[1];

    printf("\r\nx: %d y: %d",curX, curY);

    GD.Begin(POINTS);
    GD.VertexFormat(0);
    GD.ColorRGB(0xFFFFFF);
    GD.PointSize(5);
    GD.ColorA(0xff); // Draw foreground vectors
    GD.BlendFunc(SRC_ALPHA, ONE);

    GD.Vertex2f(curX, curY);
    GD.Vertex2f(curX, curY); //additive

}
