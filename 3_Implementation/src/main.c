#ifndef F_CPU
#define F_CPU 16000000UL // telling controller crystal frequency (16 MHz AVR ATMega328P)
#endif

#include <io.h> //header to enable data flow control over pins. Defines pins, ports, etc.
#include <delay.h> //header to enable delay function in program

#define BUTTON1 2 // button switch connected to port B pin 2
#define DEBOUNCE_TIME 25 // time to wait while "de-bouncing" button
#define LOCK_INPUT_TIME 300 // time to wait after a button press

// Timer0, PWM  Initialization
void timer0_init()
{
	// set up timer OC0A,OC0B pin in toggle mode and CTC mode
	TCCR0A |= (1 << COM0A1)|(1 << COM0B1)|(1 << WGM00)|(1 << WGM01);
	// set up timer with prescaler = 256
	TCCR0B |= (1 << CS02);
	// initialize counter
	TCNT0 = 0;
	// initialize compare value
	OCR0A = 0;
}


// ADC Initialization
void ADC_init()
{
	// Enable ADC, sampling freq=osc_freq/128 set prescaler to max value, 128
	ADCSRA |= (1<<ADEN) | (1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0);
	
	ADMUX = (1<<REFS0); // Select Voltage Reference (AVCC)
}

// Button switch status
unsigned char button_state()
{
	/* the button is pressed when BUTTON1 bit is clear */
	if (!(PINB & (1<<BUTTON1)))
	{
		_delay_ms(DEBOUNCE_TIME);
		if (!(PINB & (1<<BUTTON1))) return 1;
	}
	return 0;
}

// Ports  Initialization
void port_init()
{
	DDRB =0b00011011;  //PB0-IN1, PB1-IN2,PB3-IN3, PB4-IN4, PB2 - BUTTON SWITCH DIRECT
	PORTB=0b00010110;

	DDRD =0b01100000;  //PD5-ENB (OC0B), PD6-ENA (OC0A)
	PORTD=0b00000000;

	DDRC =0b00000000; // PC0-ADC
	PORTC=0b00000000; // Set all pins of PORTC low which turns it off.
}

// This function reads the value of the  analog to digital convert.
uint16_t get_LightLevel()
{
	_delay_ms(10); // Wait for some time for the channel to get selected
	ADCSRA |= (1<<ADSC); // Start the ADC conversion by setting ADSC bit.  Write 1 to ADSC

	while(ADCSRA & (1<<ADSC)); // Wait for conversion to complete
							   // ADSC becomes 0 again till then, run loop continuously
	_delay_ms(10);
	return(ADC); // Return the 10-bit result
}

// This function Re-maps a number from one range (0-1023) to another (0-100). 
uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


int main(void)
{
	uint16_t i1=0;

	port_init();
	timer0_init();
	ADC_init(); // initialization ADC
	

	while (1)
	{
		i1=map(get_LightLevel(),0,1023,0,100);

		OCR0A=i1; // Set output compare register channel A
		OCR0B=100-i1; // Set output compare register channel B (inverted)

		if (button_state()) // If the button is pressed, toggle the LED's state and delay for 300ms (#define LOCK_INPUT_TIME)
		{
			PORTB ^= (1<<0); // toggling the current state of the pin IN1. 
			PORTB ^= (1<<1); // toggling the current state of the pin IN2. Reverse the rotational direction of the motor 

			PORTB ^= (1<<3); // toggling the current state of the pin IN3. 
			PORTB ^= (1<<4); // toggling the current state of the pin IN4. LED Tape is turn off/on.
			_delay_ms(LOCK_INPUT_TIME);
		}
	};
	return (0);
}
