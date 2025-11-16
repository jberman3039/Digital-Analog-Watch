# Digital-Analog-Watch
The "Digital Analog Watch" is an ATTiny85-based project that displays hours and minutes using and outer and inner rings of LEDs respectively. The project includes a custom drivers to set and get the time for an D3231 RTC via I2C communication and update the LEDs on the PCB with 74HC595 shift registers. To initially set the time on the RTC, uncomment "#define SET_TIME" in main.c and set the values for HOUR, MINUTE, and SECOND. After initially flashing and running the code, this line must be recommented out and the code reflashed. The RTC will continue to keep accurate time as long as VBAT is connected to a power source such as a CR2032 coin cell battery. To flash the code to the ATTiny85, navigate to the src folder and run the command "make flash". This project was inspired by https://github.com/brunob45/watch/tree/master.

# PCB
The PCB was designed in KiCad 9.0.
(https://github.com/jberman3039/Digital-Analog-Watch/blob/main/images/PCB.png)
