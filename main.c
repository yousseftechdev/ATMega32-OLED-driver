#include <avr/interrupt.h>
#include <util/delay.h>
#include "OLED_interface.h"

int main()
{
    sei();
    OLED_vInit();
    OLED_vClear();
    OLED_vSquareOutline(0, 0, 32, 32, 1);
    while (1)
    {
        // for (u8 i = 0; i < 64; i++)
        // {
        //     OLED_vSquareOutline(0, 0, i*2, i, 1);
        //     OLED_vSquare(0, 0, i*2, i);
        //     _delay_ms(20);
        //     OLED_vClear();
        // }
        // OLED_vClear();
        // _delay_ms(100);
    }
}