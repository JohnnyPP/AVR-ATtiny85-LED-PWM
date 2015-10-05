/*
 * main.c
 *
 *  Created on: Oct 4, 2015
 *      Author: JohnnyP
 *      http://www.ermicro.com/blog/?p=224
 */

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
  int ipwm;
  // Initial Port I/O
  DDRB=0xFF;           // Set PORTB as Output
  // Initial PWM
  (*(volatile uint8_t *)((0x2A) + 0x20)) = 0b10000011; // Fast PWM 8 Bit
  (*(volatile uint8_t *)((0x33) + 0x20)) = 0b00000001; // No Prescaler
  TCNT0 = 0;           // Reset TCNT0

  for(;;) {            // Loop Forever
    ipwm=0;
    while (ipwm <= 255) {
      (*(volatile uint8_t *)((0x29) + 0x20))=ipwm++;
      _delay_ms(2);    // Delay 2 millisecond
    }
    ipwm=255;
    while (ipwm >= 0) {
    	(*(volatile uint8_t *)((0x29) + 0x20))=ipwm--;
      _delay_ms(2);    // Delay 2 millisecond
    }
    _delay_ms(100);    // Delay 100 millisecond
  }
  return 0;            // Standard Return Code
}

