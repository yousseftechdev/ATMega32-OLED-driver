#include "OLED_interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
    sei();
    OLED_vInit();

    u8 size = 60;
    u8 shrinking = 1;

    while (1)
    {
        // 1. Clear the entire screen (Takes ~2ms at 400kHz)
        OLED_vClear();

        // 2. Draw the current state of the animation
        // We draw all the nested outlines from the outside in
        for (u8 current_size = size; current_size >= 2; current_size -= 2)
        {
            u8 x = (128 - current_size) / 2;
            u8 y = (64 - current_size) / 2;
            
            // Your safe, 4-border outline function uses 0 extra RAM!
            OLED_vClear();
            OLED_vRectangle(x, y, current_size, current_size, 2); 
        }

        // 3. Update the animation state
        if (shrinking) {
            size -= 2;
            if (size <= 10) shrinking = 0; // Reverse direction
        } else {
            size += 2;
            if (size >= 60) shrinking = 1; // Reverse direction
        }

        _delay_ms(100); // Control animation speed
    }
}