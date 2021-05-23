#include "term-font.h"
//#include "GD2.h"
#include <string.h>

#define TERMINAL_KEY_BELL 7
#define TERMINAL_KEY_BACKSPACE 8
#define TERMINAL_KEY_CR 13
#define TERMINAL_KEY_LF 10
#define TERMINAL_KEY_SPACE 32
#define TERMINAL_KEY_ESC 27
#define TERMINAL_KEY_DEL 127

extern volatile uint8_t *spi_ctl;

const int char_height = 8;
const int char_width = 8;

const int width = 1280 / char_width;
const int height = 720 / char_height;

/* 2D array declaration*/
int display[width][height];

int cur_x = 0;
int cur_y = 0;

void thostcmd(byte a)
{
    BIT_SET(*spi_ctl, GPU_CS);
    SPI.transfer(a);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    BIT_CLEAR(*spi_ctl, GPU_CS);
}

byte get_ident()
{
    return GD.rd(REG_ID);
}

void draw_screen()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            byte newchar = display[x][y];
            int new_line = 0;

            switch (newchar)
            {
            case TERMINAL_KEY_CR:
            case TERMINAL_KEY_LF:
                new_line = 1;
                break;
            case TERMINAL_KEY_SPACE:
            case NULL:
                break;
            default:
                char str[2] = {newchar, '\0'};
                GD.cmd_text((x * char_width) + 8, (y * char_height) + 8, AMIGA4EVER_HANDLE, OPT_CENTER, str);
            }

            if (new_line)
                break;
        }
    }
}

void draw_char(char newchar, int x, int y)
{

    if (x >= width || y >= height)
        return;

    display[x][y] = newchar;
}

void draw_string(const char *str, int x, int y)
{

    size_t size = strlen(str);
    for (int i = 0; i < size; i++)
    {
        draw_char(str[i], x + i, y);
    }
}

void scroll_up()
{

    for (int y = 1; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int newrow = y;
            if (newrow == height - 1)
                display[x][newrow] = 0;
            else
                display[x][y - 1] = display[x][y];
        }
    }
}

void append_char(char newchar)
{

    if (cur_x >= width || newchar == TERMINAL_KEY_CR || newchar == TERMINAL_KEY_CR)
    {
        cur_x = 0;
        cur_y++;

        if (cur_y >= height)
        {
            scroll_up();
            cur_y = height - 1;
        }
    }

    display[cur_x][cur_y] = newchar;
    cur_x++;
}

uint8_t volatile *keyb_data = (uint8_t volatile *)0xf00019;
uint8_t volatile *keyb_count = (uint8_t volatile *)0xf0001b;

int main()
{

    printf("\r\n\r\nHello world\r\n");

    GD.begin(0);

    byte r = get_ident();

    if (r != 0x7c)
        exit(1);

    uint16_t err = GD.rd16(REG_CMD_READ);
    if (err == 0xfff)
    {
        printf("\r\nAlert %0x\r\n", err);
        exit(1);
    }
    LOAD_ASSETS();

    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.swap();

    byte key = 0;
    uint8_t count = 0;
    int key_press = 0;

    while (key != TERMINAL_KEY_ESC)
    {
        key_press = 0;

        count = *keyb_count;
        if (count > 0)
        {
            printf("buffer size: %d\r\n", count);
            key = *keyb_data;
            if (key != 0x00)
                key_press = 1;
        }

        if (key_press)
        {

            printf("Char: %0X\r\n", key);
            GD.ClearColorRGB(0x103000);
            GD.Clear();

            append_char(key);
            printf("x: %d y: %d\r\n",cur_x, cur_y);

            draw_screen();

            GD.swap();
        }
    }

    printf("\r\nend\r\n");

    exit(0);
}