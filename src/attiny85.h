// Port B Input Register 0x16 with 0x20 offset
#define PINB *((volatile unsigned char*)0x36)

// Port B Data Direction Register 0x17 with 0x20 offset
#define DDRB *((volatile unsigned char*)0x37)

// Port B Data Register 0x18 with 0x20 offset
#define PORTB *((volatile unsigned char*)0x38)

// Timer Counter Control Register B 0x33 with 0x20 offset
#define TCCR0B *((volatile unsigned char*)0x53)

// Timer/Counter Interrupt Mask Register 0x39 with 0x20 offset
#define TIMSK *((volatile unsigned char*)0x59)

// Status Register 0x3F with 0x20 offset
#define SREG *((volatile unsigned char*)0x5F)