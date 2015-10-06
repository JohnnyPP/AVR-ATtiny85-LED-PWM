/*
 * main.c
 *
 *  Created on: Oct 4, 2015
 *      Author: JohnnyP
 *      http://www.ermicro.com/blog/?p=224
 */



#include <avr/io.h>
#include <util/delay.h>

//#define TCCR0A (*(volatile uint8_t *)((0x2A) + 0x20))
#define TCCR0B (*(volatile uint8_t *)((0x33) + 0x20))
#define TCCR0A _SFR_IO8(0x2A)
#define OCR0A (*(volatile uint8_t *)((0x29) + 0x20))

#define WGM00 0
#define WGM01 1
#define FOC0A 7

int main(void)
{
	int i = 0;

	DDRB |= 1 << PINB0;  // Set PORTB PINB0 as PWM Output (Pin #5 OC0A)

	// Data sheet p79 PWM mode 3 (WGM02 -> 0 WGM01 ->1 WGM00 -> 1) Fast PWM 0xFF BOTTOM(2) MAX(1)
	/* Bits 1:0 – WGM0[1:0]: Waveform Generation Mode
	Combined with the WGM02 bit found in the TCCR0B Register, these bits control the counting sequence of the
	counter, the source for maximum (TOP) counter value, and what type of waveform generation to be used, see
	Table 11-5. Modes of operation supported by the Timer/Counter unit are: Normal mode (counter), Clear Timer on
	Compare Match (CTC) mode, and two types of Pulse Width Modulation (PWM) modes (see “Modes of Operation”
	on page 71)*/

	//TCCR0A = 0b10000011;
	TCCR0A |= (1 << FOC0A) | (1 << WGM01) | (1 << WGM00);

	// Data sheet p80 Clock Select Bit Description CS00 -> 1 clkI/O/(No prescaling)
	// Note that if you do not initialize this register,
	// all the bits will remain as zero and the timer/counter will remain stopped.
	//TCCR0B = 0b00000001;
	TCCR0B |= 1 << CS00;

	// Initialize counter
	TCNT0 = 0;

	while(1)
	{
		while (i < 255)
		{
			// By varying the OCR0A register the width of the pulse is modulated
			OCR0A = i++;
			_delay_ms(4);
		}

		while (i > 0)
		{
			OCR0A = i--;
			_delay_ms(8);
		}
	}
	return 0;
}

