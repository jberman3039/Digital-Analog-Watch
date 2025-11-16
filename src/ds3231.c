#include "attiny85.h"
#include "i2c.h"

void get_seconds(unsigned char* seconds)
{
	unsigned char seconds_register;
	i2c_start();
	i2c_tx(0xD0); // Send slave address with write bit
	i2c_tx(0x00); // Seconds register
	i2c_stop();

	i2c_start();
	i2c_tx(0xD1); // Send slave address with read bit
	seconds_register = i2c_rx(); // Read response
	i2c_stop();

	*seconds = (seconds_register & 0x0F) + (10 * (seconds_register >> 4));
}

void get_minutes(unsigned char* minutes)
{
	unsigned char minutes_register;

	i2c_start();
	i2c_tx(0xD0); // Send slave address with write bit
	i2c_tx(0x01); // Minutes register
	i2c_stop();

	i2c_start();
	i2c_tx(0xD1); // Send slave address with read bit
	minutes_register = i2c_rx(); // Read response
	i2c_stop();

	*minutes = (minutes_register & 0x0F) + (10 * (minutes_register >> 4));
}

void get_hours(unsigned char* hours)
{
	unsigned char hours_register;

	i2c_start();
	i2c_tx(0xD0); // Send slave address with write bit
	i2c_tx(0x02); // Hours register
	i2c_stop();

	i2c_start();
	i2c_tx(0xD1); // Send slave address with read bit
	hours_register = i2c_rx(); // Read response
	i2c_stop();

	*hours = hours_register & 0x0F;
	if (hours_register & 0b00010000) *hours += 10; // Check the 10 hour bit
}

void set_seconds(unsigned short seconds)
{
	unsigned char seconds_register_data = 0x00;

	// Set the second (1-9) in the first 4 bits and the 10 seconds in the next 3 bits
	seconds_register_data |= (seconds % 10);
	seconds_register_data |= ((seconds / 10) << 4);

	// Set register
	i2c_start();
	i2c_tx(0xD0); // Send slave address with write bit
	i2c_tx(0x00); // Seconds register
	i2c_tx(seconds_register_data);
	i2c_stop();
}

void set_minutes(unsigned short minutes)
{
	unsigned char minutes_register_data = 0x00;

	// Set the minute (1-9) in the first 4 bits and the 10 minutes in the next 3 bits
	minutes_register_data |= (minutes % 10);
	minutes_register_data |= ((minutes / 10) << 4);

	// Set register
	i2c_start();
	i2c_tx(0xD0); // Send slave address with write bit
	i2c_tx(0x01); // Minutes register
	i2c_tx(minutes_register_data);
	i2c_stop();
}

void set_hours(unsigned short hours)
{
	unsigned char hour_register_data = 0x00;

	// Set 12hr mode
	hour_register_data |= 0b01000000;

	// Set the hour (1-9) in the first 4 bits and the 10 hour in bit 5
	hour_register_data |= (hours % 10);
	hour_register_data |= ((hours / 10) << 4);
	
	// Set register
	i2c_start();
	i2c_tx(0xD0); // Send slave address with write bit
	i2c_tx(0x02); // Hours register
	i2c_tx(hour_register_data);
	i2c_stop();
}