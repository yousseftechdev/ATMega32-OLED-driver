#include <avr/interrupt.h>
#include <util/delay.h>
#include "OLED_interface.h"

int main()
{
    sei();
    OLED_vInit();
    OLED_vClear();
    while (1)
    {
        for (u8 i = 0; i < 127; i++)
        {
            OLED_vSquare(i, 8);
            _delay_ms(50);
        }
        OLED_vClear();
    }
}