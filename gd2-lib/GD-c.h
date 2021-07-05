#ifndef GDC_DEFINED
#define GDC_DEFINED	86631	/* Revision ID */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void gd_begin();
void gd_clear();
void gd_clearColor(uint32_t *color);
void gd_swap();
void gd_line(uint32_t * x1, uint32_t * y1, uint32_t * x2, uint32_t * y2, uint32_t * size, 
                    uint32_t * color, uint32_t *begin );
void gd_text(uint32_t * x, uint32_t * y, uint32_t * justify, const char *text, uint32_t * height, 
                uint32_t * width, uint32_t * color, uint32_t * font, uint32_t *begin );
void gd_plot(uint32_t *x, uint32_t *y, uint32_t *color, uint32_t *size, uint32_t *begin) ;


#ifdef __cplusplus
}
#endif

#endif