#include <cstdio>
#include <bitset>
#include <string>

uint8_t volatile *spi_ctl = (uint8_t volatile *)0xf40009;
uint8_t volatile *data_in = (uint8_t volatile *)0xf4000b;
uint8_t volatile *data_out = (uint8_t volatile *)0xf4000d;

using namespace std;


int main() {

    printf("\r\n\r\nhello: %d, %.2f\r\n", 12, 10.63);

    std::bitset<8> byte8;

    byte8 = *spi_ctl;

    if (byte8.test(5)) 
        printf("true\r\n");
    
}
