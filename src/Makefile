compile:
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os main.c -o main.o
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os i2c.c -o i2c.o
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os ds3231.c -o ds3231.o
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os 74hc595.c -o 74hc595.o

flash:
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os main.c -o main.o
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os i2c.c -o i2c.o
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os ds3231.c -o ds3231.o
	avr-gcc -c -mmcu=attiny85 -DF_CPU=8000000UL -Os 74hc595.c -o 74hc595.o
	avr-gcc -mmcu=attiny85 main.o i2c.o ds3231.o 74hc595.o -o proj.elf
	avr-objcopy -O ihex -j .text -j .data proj.elf proj.hex
	avrdude -p t85 -c usbtiny -U flash:w:proj.hex:i
