#define F_CPU 1000000UL  // 1 MHz
#define BAUD_RATE 4800   //serial comm baud rate
#define SPEED_TIMER 3

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "led.h"
#include "serial.h"
#include "sensors.h"
#include "string.h"
#include "pwm.h"


int dist,speed;
uint8_t adc;

int main(){
//initializing a2d converter
	adc_init();

// initialize fast PWM on PB1 (OSCR1A)
	setup_pwm();

// setting up serial communication 8E2 asynchronous mode.
// 4800 baud , 8 data bits , two stop bits, even parity.
	serial_init(BAUD_RATE);
	//serial_init(4800);

//initilize LEDs
	init_leds();

// initial blink
startblink();
OCR1A = 0x0001;
char* c = "hello";
char d;
int ij = 0;
while (c[ij] != '\x0') {
  _serial_write((uint8_t)c[ij]);
  _delay_ms(50);
  ij=ij+1;
}
//_serial_write((uint8_t)strlen(c));

// main loop that polls the distance sensor.
     	while(1){

		//start
		//_serial_test(a);
                //_serial_write('\n');
                //_serial_write('\r');
//		_serial_test(a);
		//blink();
  //serial_print(c);
		if (((UCSRA & 0b00000010) >> 1) == 1) { blink; }

// 		adc = get_adc();
// 		_serial_write_number(adc);
// 		OCR1A = adc;
// 		char* s;
// 		s = "hello there";
// 		serial_print(s);
// _serial_write('a');

 		//serial_print(c);
 		_delay_ms(150);
 // blink();
  
  
		//_serial_write((unsigned char)adc);
		//if (TCNT1 > OCR1A) { turnOntest(); }
		//else { turnOfftest(); }
//		else { turnOfftest(); }
		//dist = get_distance(adc);
		//if(dist)
		//	turnOnLed1();
		//else
		//	turnOffLed1();
		//if ((TIFR & 0b00010000) == 0b00010000) { turnOnLed1(); }
		//else { turnOffLed1(); }
/*
blink();
		speed = get_speed();
		update_led_brightness(speed);
blink();
		//print dist and speed.
                _serial_write((unsigned char)speed+0x30);
                _serial_write((unsigned char)dist+0x30);
blink();
		//end*/
		//_serial_write('e');
                //_serial_write('\n');
                //_serial_write('\r');
//blink();

            }
	return 0;
}

