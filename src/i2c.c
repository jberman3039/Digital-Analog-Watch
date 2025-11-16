#include "attiny85.h"
#include "i2c.h"
#include <util/delay.h>


void init_i2c()
{
	// Initialize pullups
	PORTB |= (1 << SCL_PIN);
	PORTB |= (1 << SDA_PIN);

	// Set SCL/SDA to output
	DDRB |= (1 << SCL_PIN);
	DDRB |= (1 << SDA_PIN);
}

void i2c_start()
{
	// Set SDA to output
	DDRB |= (1 << SDA_PIN);

	// Generate start condition
	PORTB |= (1 << SDA_PIN); //SDA high
	_delay_us(5);
	PORTB |= (1 << SCL_PIN); //SCL high
	_delay_us(5);
	PORTB &= ~(1 << SDA_PIN); //SDA low
	_delay_us(5);
	PORTB &= ~(1 << SCL_PIN); //SCL low
	_delay_us(5);
}

void i2c_stop()
{
	// Set SDA to output
	DDRB |= (1 << SDA_PIN);

	PORTB &= ~(1 << SDA_PIN); //SDA low
	_delay_us(5);
	PORTB |= (1 << SCL_PIN); //SCL high
	_delay_us(5);
	PORTB |= (1 << SDA_PIN); //SDA high
	_delay_us(5);
}

void i2c_tx(unsigned char data_tx)
{
	unsigned short i;
	char ack;

	// Set SDA to output
	DDRB |= (1 << SDA_PIN);

	for (i = 0; i < 8; i++)
	{
		// Send bit
		if (data_tx & 0x80)
			PORTB |= (1 << SDA_PIN); //SDA high
		else
			PORTB &= ~(1 << SDA_PIN); //SDA low
		_delay_us(5);
		
		// Pulse SCL
		PORTB |= (1 << SCL_PIN); //SCL high
		_delay_us(5);
		PORTB &= ~(1 << SCL_PIN); //SCL low

		// Next bit
		data_tx <<= 1;
	}

	PORTB &= ~(1 << SCL_PIN); //SCL low
	PORTB |= (1 << SDA_PIN); // reenable pullup on SDA
	DDRB &= ~(1 << SDA_PIN); // set SDA as input


	// Pulse SCL
	PORTB |= (1 << SCL_PIN); //SCL high
	_delay_us(5);

	ack = PINB & (1 << SDA_PIN);

	PORTB &= ~(1 << SCL_PIN); //SCL low
	_delay_us(5);
}

unsigned char i2c_rx()
{
	unsigned char data_rx;
	unsigned short i;

	PORTB &= ~(1 << SCL_PIN); //SCL low
	PORTB |= (1 << SDA_PIN); // reenable pullup on SDA
	DDRB &= ~(1 << SDA_PIN); // set SDA as input

	for (i = 0; i < 8; i++)
	{
		data_rx <<= 1;

		// Toggle SCL
		PORTB |= (1 << SCL_PIN); //SCL high
		_delay_us(5);
		
		if (PINB & (1 << SDA_PIN))
		{
			data_rx |= 0x01;
		}

		//Toggle SCL
		PORTB &= ~(1 << SCL_PIN); //SCL low
		_delay_us(5);
	}

	return data_rx;
}