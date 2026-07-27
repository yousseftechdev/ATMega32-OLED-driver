#include <avr/interrupt.h>
#include <util/delay.h>
#include "OLED_interface.h"

int main () {
    sei();
    OLED_vInit();
    OLED_vSquare(100, 8);
    while (1) {
        // OLED_vSendCmd(0xA7);
        // _delay_ms(200);
        // OLED_vSendCmd(0xA6);
        // _delay_ms(200);
    }
}