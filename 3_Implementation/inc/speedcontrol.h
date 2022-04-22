#ifndef F_CPU
#define F_CPU 16000000UL // telling controller crystal frequency (16 MHz AVR ATMega328P)
#endif

#include <io.h> //header to enable data flow control over pins. Defines pins, ports, etc.
#include <delay.h> //header to enable delay function in program

#define BUTTON1 2 // button switch connected to port B pin 2
#define DEBOUNCE_TIME 25 // time to wait while "de-bouncing" button
#define LOCK_INPUT_TIME 300 // time to wait after a button press
