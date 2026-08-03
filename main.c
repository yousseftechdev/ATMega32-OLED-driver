#include "OLED_interface.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int main(void)
{
    sei();                 /* TWI layer is interrupt-driven */
    OLED_vInit();          /* 400 kHz I²C + SSD1306 init sequence */
    OLED_vClear();
    OLED_vText(0, 0, "HELLO WORLD");
    OLED_vCircle(96, 32, 10);
    _delay_ms(50);
    
    /* Marquee: scroll the whole screen left, 4-frame interval */
    OLED_vScrollH(OLED_SCROLL_LEFT, 0, 7, OLED_SCROLL_4FR);

    while (1);             /* The SSD1306 now scrolls with 0% CPU usage */
}