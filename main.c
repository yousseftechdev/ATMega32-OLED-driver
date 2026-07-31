#include "OLED_interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
    sei();
    OLED_vInit();
    OLED_vClear();
    char character = 65;
    for (u8 i = 0; i < 64; i += 8)
    {
        for (u8 j = 0; j < 128; j += 6)
        {
            OLED_vChar(j, i, character);
            character++;
            if (character >= 90) break;
        }
        if (character >= 90) break;
    }
    return 0;
}