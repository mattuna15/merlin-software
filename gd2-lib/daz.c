#include "GD2.h"
#include "GD-c.h"
#include <stdio.h>

/*
GD.ColorA(0x30); // Draw background glows
GD.LineWidth(48);
drawgame();
GD.ColorA(0xff); // Draw foreground vectors
GD.LineWidth(10);
GD.BlendFunc(SRC_ALPHA, ONE); // additive blending
*/

#define CUR 1
#define VEC 2
#define SVEC 3

int vectors[49][8] =
    {
        {1, 0, 512, 0, 0, 128, 0, 0},
        {2, 7, 4, 0, 0, 0, 0, 0},
        {2, 9, 1, 7, 1023, 0, 1023, 0},
        {2, 9, 1, 7, 0, 767, 0, 767},
        {2, 9, 1, 7, -1023, 0, -1023, 0},
        {2, 9, 1, 7, 0, -767, 0, -767},
        {2, 9, 1, 7, 767, 767, 767, 767},
        {2, 8, 2, 7, 512, -512, 256, -256},
        {2, 8, 2, 7, -1022, -1022, -511, -511},
        {2, 9, 1, 7, -512, 512, -512, 512},
        {2, 8, 2, 7, 512, 510, 256, 255},
        {2, 9, 1, 7, 767, -767, 767, -767},
        {1, 0, 512, 0, 1023, 895, 0, 0},
        {2, 7, 4, 0, 0, 0, 0, 0},
        {2, 9, 1, 7, -767, -767, -767, -767},
        {2, 8, 2, 7, -512, 510, -256, 255},
        {2, 9, 1, 7, 512, 512, 512, 512},
        {2, 8, 2, 7, 1022, -1022, 511, -511},
        {2, 8, 2, 7, -512, -512, -256, -256},
        {2, 9, 1, 7, -767, 767, -767, 767},
        {1, 0, 512, 0, 500, 508, 0, 0},
        {2, 7, 4, 0, 0, 0, 0, 0},
        {3, 2, 128, 13, 3, 0, 6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 12, -3, 0, -6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 11, 3, 0, 6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 10, -3, 0, -6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 9, 3, 0, 6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 8, -3, 0, -6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 7, 3, 0, 6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 6, -3, 0, -6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 5, 3, 0, 6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 4, -3, 0, -6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 3, 3, 0, 6, 0},
        {3, 1, 256, 0, 0, 1, 0, 1},
        {3, 2, 128, 2, -3, 0, -6, 0},
};

int main()
{
    printf("\r\n\r\nLines Demo\r\n");

    GD.storage();
    GD.begin();

    GD.ClearColorRGB(0x0);
    GD.Clear();

    int curX = 0;
    int curY = 0;

    for (int vec = 0; vec < 49; vec++)
    {

        if (vectors[vec][0] == CUR)
        {
            GD.Begin(LINES);
            GD.VertexFormat(0);
            GD.ColorRGB(0xFFFFFF);
            curX = vectors[vec][4] + 20;
            curY = vectors[vec][5] - 128;
            printf("\r\nX: %d Y: %d\r\n", curX, curY);
        }
        else
        {

            int prevX = curX;
            int prevY = curY;

            int diffX = vectors[vec][6];
            int diffY = vectors[vec][7];

            int brightness = vectors[vec][3];
            if (brightness == 0)
                GD.ColorRGB(0x0);
            else
                GD.ColorRGB(0xFFFFFF);


            GD.ColorA(0x30 + brightness); // Draw background glows
            GD.LineWidth(20);
            if (brightness > 3 && (diffX > 10 || diffY > 10))
                GD.Vertex2f(curX, curY);

            curX += diffX;
            curY += diffY;

            if (brightness > 3 && (diffX > 10 || diffY > 10))
                GD.Vertex2f(curX, curY);

            GD.BlendFunc(SRC_ALPHA, ONE);
            GD.ColorA(0xff); // Draw foreground vectors
            GD.LineWidth(brightness);
            GD.Vertex2f(prevX, prevY);
            GD.Vertex2f(curX, curY);
        }
    }

    GD.swap();
}
