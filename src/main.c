#include "attiny85.h"
#include "i2c.h"
#include "ds3231.h"
#include "74hc595.h"

//#define SET_TIME // Uncomment to set the current time with the values below on startup
#define HOUR 3
#define MINUTE 34
#define SECOND 50 

volatile char update_counter = 0; // Counter updated by timer0 to control LED update frequency
const char update_period = 5; // Period to update the time at

// Timer/Counter0 Overflow interrupt (interupt vector #5)
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	update_counter++;
}

int main()
{
	// Variables to store the time data from the RTC
	unsigned char rtc_hour;
	unsigned char rtc_minute;

	// Init functions
	init_i2c();
	init_74hc595();

	// Start timer at 1/1024 system clock rate
	TCCR0B |= (1 << 2) | (1 << 0);

	// Enable Time/Counter0 Overflow Interrupt
	TIMSK |= (1 << 1);

	// Enable Global Interrupts
	SREG |= (1 << 7);


	// Set time on the DS3231
	#ifdef SET_TIME
		set_hours(HOUR);
		set_minutes(MINUTE);
		set_seconds(SECOND);
	#endif
		
	// Set inital time on the watch
	get_hours(&rtc_hour);
	get_minutes(&rtc_minute);
	update_time(&rtc_hour, &rtc_minute);


	while (1)
	{
		if (update_counter > update_period)
		{
			// Reset counter
			update_counter = 0;

			// Update time on watch
			get_hours(&rtc_hour);
			get_minutes(&rtc_minute);
			update_time(&rtc_hour, &rtc_minute);
		}
	}
}