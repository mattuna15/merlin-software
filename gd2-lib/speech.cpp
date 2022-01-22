#include "converted-assets/noisy_assets.h"
#include "GD2.h"

void setup()
{
  printf("\r\n\r\nCSound Demo\r\n");

  GD.storage();
  GD.begin();
  GD.Clear();
  LOAD_ASSETS();

  GD.ClearColorRGB(0x0);
  GD.Clear();
}

static void saydigit(byte n)
{
    GD.ClearColorRGB(0x101000); // JCB{
    GD.Clear();
    GD.cmd_number(240, 136, 31, OPT_CENTER, n);
    GD.swap();
    GD.flush();
    // }JCB
    uint32_t base, len;
    switch (n)
    {
    case 0:
        base = DIGIT_0;
        len = DIGIT_0_LENGTH;
        break;
    case 1:
        base = DIGIT_1;
        len = DIGIT_1_LENGTH;
        break;
    case 2:
        base = DIGIT_2;
        len = DIGIT_2_LENGTH;
        break;
    case 3:
        base = DIGIT_3;
        len = DIGIT_3_LENGTH;
        break;
    case 4:
        base = DIGIT_4;
        len = DIGIT_4_LENGTH;
        break;
    case 5:
        base = DIGIT_5;
        len = DIGIT_5_LENGTH;
        break;
    case 6:
        base = DIGIT_6;
        len = DIGIT_6_LENGTH;
        break;
    case 7:
        base = DIGIT_7;
        len = DIGIT_7_LENGTH;
        break;
    case 8:
        base = DIGIT_8;
        len = DIGIT_8_LENGTH;
        break;
    case 9:
        base = DIGIT_9;
        len = DIGIT_9_LENGTH;
        break;
    }
    GD.sample(base, len, 8000, ADPCM_SAMPLES);
}

int main()
{
    setup();

    for (byte n = 0; n < 10; n++)
    {
        GD.Clear();
        GD.cmd_number(240, 136, 31, OPT_CENTER, n);
        GD.swap();
        printf("\r\n number: %d\r\n", n);
        saydigit(n);
        getchar();
    }

} //' }A
