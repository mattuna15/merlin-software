#include <stdint.h>
#include "GD-c.h"
#include <stdio.h>
#include "GD2.h"


void gd_begin() {
    
    printf("\r\nChecking for Gameduino\r\n");

    GD.begin(0);

    byte r = GD.rd(REG_ID);

    if (r != 0x7c)
        exit(1);
    
    printf("\r\nGameduino found with ident: %0X\r\n",r);

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

void gd_clear() {
    GD.Clear();
}

void gd_clearColor(uint32_t *color) {
    GD.ClearColorRGB(*color);
}

void gd_swap() {
    GD.swap();  
}


void gd_line(uint32_t * x1, uint32_t * y1, uint32_t * x2, uint32_t * y2, uint32_t * size, 
                    uint32_t * color, uint32_t *begin ) {

    
    if (*begin == 1)
        GD.Begin(LINES);

    GD.PointSize(16 * *size);
    GD.ColorRGB(*color);
    GD.VertexFormat(0);

    GD.Vertex2f(*x1, *y1);     
    GD.Vertex2f(*x2, *y2);

}

void gd_text(uint32_t * x, uint32_t * y, uint32_t * justify, const char *text, uint32_t * height, 
                uint32_t * width, uint32_t * color, uint32_t * font, uint32_t *begin ) {

    if (*begin == 1)
        GD.Begin(BITMAPS);

    GD.ColorRGB(*color);
    GD.cmd_text((*x * *width) + 8, (*y * *height) + 8, *font, *justify, text);

}

void gd_plot(uint32_t *x, uint32_t *y, uint32_t *color, uint32_t *size, uint32_t *begin) {
    
    printf("\r\nplot: ");
    int pointSize = 16 * *size;
    
    if (*begin == 1)
        GD.Begin(POINTS);

    GD.PointSize(pointSize);
    GD.ColorRGB(*color);
    GD.VertexFormat(0);

    GD.Vertex2f(*x, *y);


}