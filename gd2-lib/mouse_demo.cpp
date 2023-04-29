#include "mouseasset.h"


void setup() {


  GD.begin();
  LOAD_ASSETS();

}



int main() {


    setup();

    while (true)
    {
        /* code */

    GD.ClearColorRGB(0x103000);
    GD.Clear();
    for (int i = 0; i < 16; i++) {
        int x = (i & 8) ? 260 : 20;
        int y = 12 + 33 * (i % 8);
        GD.BlendFunc(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);
        GD.cmd_number(x, y, 26, OPT_CENTERY, 16 + i);
    // GD.BlendFunc(SRC_ALPHA, ZERO);
        GD.cmd_text(x + 20, y, 16 + i, OPT_CENTERY, "This font");
    }

     GD.BlendFunc(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);
    // GD.BlendFunc(SRC_ALPHA, ZERO);
    GD.cmd_text(400, 400, ATARIST8X16SYSTEMFONT_HANDLE, OPT_CENTERY, "This atari font");


    GD.Begin(BITMAPS);
    GD.Vertex2ii(400, 450, POINTER_HANDLE);

    GD.swap();


    }


}