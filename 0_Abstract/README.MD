# Introduction
A simple electrical circuit is made to control the speed of DC motor using LDR(Light Dependent Resistor). LDR whose resistance is inversely proportional to the intensity of light is often used as a sensor in electronic projects that involve the use of light. Light Dependent Resistor and AVR microcontroller ATmega328 features such as Analog to Digital Conversion are used to measure the light intensity. Also Dual H-Bridge Motor Driver Module-L298N is used in controlling motor speed and direction. A switch is also added to this circuit to toggle the direction of rotation of the motor.

# PWM(Pulse Width Modulation) mode
Pulse Width Modulation (PWM) is a very common technique in telecommunication and power control. It is commonly used to control the power fed to an electrical device, whether it is a motor, an LED, speakers, etc. It is basically a modulation technique, in which the width of the carrier pulse is varied in accordance with the analog message signal.
For making PWM, AVR contains separate hardware! By using this, the CPU instructs the hardware to produce PWM of a particular duty cycle. The ATmega328 has 6 PWM outputs, 2 are located on timer/counter0 (8bit), 2 are located on timer/counter1 (16bit), and 2 is located on timer/counter2 (8bit). Timer/Counter0 is the simplest PWM device on the ATmega328.

Initialize Timer0 in PWM mode:

TCCR0A |=(1 << WGM00)|(1 << WGM01) - set up WGM: Fast PWM

TCCR0A |= (1 << COM0A1)|(1 << COM0B1) - set up compare output mode A,B

TCCR0B |= (1 << CS02) - set up timer with prescaler = 256

# ADC(Analog to Digital)
Light Dependent Resistor (LDR) is a transducer which changes its resistance when light falls on its surface changes.
For transferring external continuous information (analog information) into a digital/computing system, we must convert them into integer (digital) values. This type of conversion is carried out by Analog to Digital Converter (ADC). The process of converting an analog value into digital value is known as Analog to Digital Conversion.
Digital signals are analog equivalents in digital or numeric format which are well understood by digital systems like microcontrollers. ADC is one such hardware which measures analog signals and produces a digital equivalent of the same signal. AVR microcontrollers has inbuilt ADC facility to convert analog voltage into an integer. AVR convert it into 10-bit number of range 0 to 1023.

Initialize ADC:

TADCSRA |= (1<<ADEN) - Enable ADC

ADCSRA |= (1<<ADPS2)| (1<<ADPS1)| (1ADPS0) - set up ADC prescaler = 128

ADMUX = (1 << REFS0) - set up voltage referance = AVCC; - set up Input Channel = ADC0

# Motor driver module-L298N
DC motor driver is used because microcontrollers are not capable of delivering current not more than 100 milliamps in general. This module will add some muscles to microcontrollers to drive high power DC motors. It can control 2 DC motors simultaneously up to 2 amps each or one stepper motor. We can control the speed using PWM and also its rotational direction of the motors.
