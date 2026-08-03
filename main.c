#include "OLED_interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

int main(void)
{
    sei();
    OLED_vInit();
    OLED_vClear();
    OLED_vCircle(32, 32, 15);
    OLED_vCircle(96, 32, 15);
    _delay_ms(10);
    while (1)
    {
        OLED_vScrollH(OLED_SCROLL_RIGHT, 2, 6, OLED_SCROLL_1FR);
        _delay_ms(20);
        OLED_vScrollStop();
        OLED_vScrollH(OLED_SCROLL_LEFT, 2, 6, OLED_SCROLL_1FR);
        _delay_ms(40);
        OLED_vScrollStop();
        OLED_vScrollH(OLED_SCROLL_RIGHT, 2, 6, OLED_SCROLL_1FR);
        _delay_ms(20);
        OLED_vScrollStop();
    }

    return 0;
}