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
void gd_text(uint32_t * x, uint32_t * y, uint32_t * font, uint32_t *color, uint32_t *text, uint32_t *len);
void gd_plot(uint32_t *x, uint32_t *y, uint32_t *color, uint32_t *size, uint32_t *begin) ;
void gd_draw_bitmap(uint32_t *x, uint32_t *y, uint32_t *size, uint32_t *handle, 
                        uint32_t *cell, uint32_t *blendsrc, uint32_t *blenddst ) ;
void gd_load_bitmapfile(uint32_t *filename, uint32_t *flen) ;
void gd_load_bitmap(uint32_t *pointer, uint32_t *count, uint32_t *asset_end );
uint32_t gd_rand(uint32_t *seed);
void gd_mode(uint32_t *mode);

#ifdef __cplusplus
}
#endif

#endif

/*  GD.Begin(BITMAPS);
  GD.BlendFunc(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);
  GD.BitmapHandle(character->spriteHandle);
  GD.BitmapSize(NEAREST, BORDER, BORDER, 24, 24);
  GD.BitmapLayout(ARGB4, 2 * 24, 24);

  GD.VertexFormat(3);
  GD.Cell(0);

  GD.Vertex2f(character->currentPosition.x * 24 * 8, character->currentPosition.y * 24 * 8); */