#include "GD2.h"


#define int1 0x64
#define int2 0x68
#define int3 0x6c
#define int4 0x70
#define int5 0x74
#define int6 0x78
#define int7 0x7c

void gd_interrupt_handler() {

    printf("\r\nBing\r\n");

    uint8_t reg_flags = GD.rd(REG_INT_FLAGS);
    GD.cmd_regwrite(REG_INT_EN, 0);

    printf("\r\n0x%X\r\n",reg_flags);
    exit(0);

}

void setGdHandler(void(*handler)()) {
	asm(
		"move.l	%0,0x70":
						: "r" (handler)
						:);

	volatile uint32_t *gd_int = (uint32_t*)int4;

	printf("\r\ngd address = 0x%0lX\r\n", *gd_int);
    GD.cmd_regwrite(REG_GPIOX, 0x808c);
    GD.cmd_regwrite(REG_INT_MASK, 0xFF);
    GD.cmd_regwrite(REG_INT_EN, 0x1);

}

void setup()
{
  printf("\r\nInterrupts Demo\r\n");

  GD.storage();
  GD.begin();
  GD.Clear();

  setGdHandler(&gd_interrupt_handler);

  GD.ClearColorRGB(0x0);
  GD.Clear();
}


int main()
{
    setup();

    GD.cmd_interrupt(200);
    GD.swap();

    uint8_t reg_flags = GD.rd(REG_INT_FLAGS);

    printf("\r\n0x%X\r\n",reg_flags);

    reg_flags = GD.rd(REG_INT_MASK);

    printf("\r\n0x%X\r\n",reg_flags);

    reg_flags = GD.rd(REG_INT_EN);

    printf("\r\n0x%X\r\n",reg_flags);

    uint16_t reg_flags2 = GD.rd16(REG_GPIOX);
    printf("\r\n0x%X\r\n",reg_flags2);
    
    getchar();
} 
