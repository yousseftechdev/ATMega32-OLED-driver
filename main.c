#include "OLED_interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
    sei();
    OLED_vInit();
    OLED_vFillCircle(32, 32, 10);
    OLED_vCircle(96, 32, 10);
    return 0;
}