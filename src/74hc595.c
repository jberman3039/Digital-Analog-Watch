#include "attiny85.h"
#include "74hc595.h"
#include <util/delay.h>

void init_74hc595()
{
	// Set shift register pins to output
	DDRB |= (1 << SRCLK_HOUR_PIN);
	DDRB |= (1 << SRCLK_MINUTE_PIN);
	DDRB |= (1 << SRCLR_PIN);

	// Clear pins high
	PORTB |= (1 << SRCLR_PIN);

	// Clear shift registers
	clear_sr();
}

void clear_sr()
{
	// Clear pin low
	PORTB &= ~(1 << SRCLR_PIN);
	_delay_us(5);

	// Pulse clock
	PORTB |= (1 << SRCLK_HOUR_PIN); 
	_delay_us(5);
	PORTB &= ~(1 << SRCLK_HOUR_PIN); 

	// Raise clear pin back
	PORTB |= (1 << SRCLR_PIN);

	// Send initial pulses to reinit shift registers (SRCLK and RCLK wired together)
	PORTB |= (1 << SRCLK_HOUR_PIN);
	PORTB |= (1 << SRCLK_MINUTE_PIN);
	_delay_us(5);
	PORTB &= ~(1 << SRCLK_HOUR_PIN);
	PORTB &= ~(1 << SRCLK_MINUTE_PIN);

}

void update_hour(unsigned char* rtc_hour)
{
	unsigned char i;
	unsigned char num_leds_hour = 1 + (*rtc_hour); // Start with 1 LED lit at the 12 o'clock position
	if (num_leds_hour == 13) num_leds_hour = 1; // Set only 1 LED for 12 o'clock

	// Update the shift register to the current hour
	for (i = 0; i < num_leds_hour; i++)
	{
		PORTB |= (1 << SRCLK_HOUR_PIN);
		_delay_us(5);
		PORTB &= ~(1 << SRCLK_HOUR_PIN);
	}
}

void update_minute(unsigned char* rtc_minute)
{
	unsigned char i;
	unsigned char num_leds_minute = 1 + (*rtc_minute) / 5; //Start with 1 LED lit at the 12 o'clock position, light LEDs at 5 minute marks

	// Update the shift register to the current 5 minute mark
	for (i = 0; i < num_leds_minute; i++)
	{
		// Update shift register
		PORTB |= (1 << SRCLK_MINUTE_PIN);
		_delay_us(5);
		PORTB &= ~(1 << SRCLK_MINUTE_PIN);
	}
}

void update_time(unsigned char* rtc_hour, unsigned char* rtc_minute)
{
	clear_sr();
	update_hour(rtc_hour);
	update_minute(rtc_minute);
}