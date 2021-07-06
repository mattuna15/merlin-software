#include <stdio.h>
#include <math.h>
#include "../GD-c.h"

int main()
{
    /* screen ( integer) coordinate */
    int iX, iY;
    const int iXmax = 400;
    const int iYmax = 400;
    /* world ( double) coordinate = parameter plane*/
    double Cx, Cy;
    const double CxMin = -2.5;
    const double CxMax = 1.5;
    const double CyMin = -2.0;
    const double CyMax = 2.0;
    /* */
    double PixelWidth = (CxMax - CxMin) / iXmax;
    double PixelHeight = (CyMax - CyMin) / iYmax;
    /* color component ( R or G or B) is coded from 0 to 255 */
    /* it is 24 bit color RGB file */
    const int MaxColorComponentValue = 255;

    static unsigned char color[3];
    /* Z=Zx+Zy*i  ;   Z0 = 0 */
    double Zx, Zy;
    double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
    /*  */
    int Iteration;
    const int IterationMax = 200;
    /* bail-out value , radius of circle ;  */
    const double EscapeRadius = 2;
    double ER2 = EscapeRadius * EscapeRadius;
    /*create new file,give it a name and open it in binary mode  */
    /* compute and write image data bytes to the file*/
    for (iY = 0; iY < iYmax; iY+=4)
    {
        Cy = CyMin + iY * PixelHeight;
        if (fabs(Cy) < PixelHeight / 2)
            Cy = 0.0; /* Main antenna */
        for (iX = 0; iX < iXmax; iX+=4)
        {
            Cx = CxMin + iX * PixelWidth;
            /* initial value of orbit = critical point Z= 0 */
            Zx = 0.0;
            Zy = 0.0;
            Zx2 = Zx * Zx;
            Zy2 = Zy * Zy;
            /* */
            for (Iteration = 0; Iteration < IterationMax && ((Zx2 + Zy2) < ER2); Iteration++)
            {
                Zy = 2 * Zx * Zy + Cy;
                Zx = Zx2 - Zy2 + Cx;
                Zx2 = Zx * Zx;
                Zy2 = Zy * Zy;
            };
            /* compute  pixel color (24 bit = 3 bytes) */
            if (Iteration == IterationMax)
            { /*  interior of Mandelbrot set = black */
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }
            else
            {                   /* exterior of Mandelbrot set = white */
                color[0] = 255; /* Red*/
                color[1] = 255; /* Green */
                color[2] = 255; /* Blue */
            };
            uint32_t colorRGB = color[0] << 16 + color[1] << 8 + color[2];
            /*write color to the file*/
            gd_plot(&iY, &iY, &colorRGB,4,0 );
        }
    }

    return 0;
}