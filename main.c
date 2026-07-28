#include <avr/interrupt.h>
#include <util/delay.h>
#include "OLED_interface.h"

int main()
{
    sei();
    OLED_vInit();
    OLED_vClear();
    OLED_vSquare(128 / 4, 64 / 4, 64, 64 / 2);
    OLED_vSquareInverted((128 / 4) + 2, (64 / 4) + 2, 64 - 4, (64 / 2) - 4);
    while (1)
    {
        // OLED_vSquare(0, 0, 64, 32);
        // _delay_ms(50);
        // OLED_vSquare(64, 0, 64, 32);
        // _delay_ms(50);
        // OLED_vSquare(0, 32, 64, 32);
        // _delay_ms(50);
        // OLED_vSquare(64, 32, 64, 32);
        // _delay_ms(50);

        // OLED_vClear();
    }
}