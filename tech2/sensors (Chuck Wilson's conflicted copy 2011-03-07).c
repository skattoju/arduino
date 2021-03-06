#define F_CPU 1000000UL
#define SPEED_TIMER 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "led.h"
#include "inttypes.h"
#include "string.h"

/* Sensor Data */

static int adc_data[5];
int sensor_data[] = {

        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,30,29,28,
        27,26,25,25,24,24,24,23,23,23,22,22,21,20,20,19,19,19,19,18,18,18,17,17,
        17,16,16,16,15,15,15,15,15,14,14,14,13,13,13,13,13,13,12,12,12,12,12,12,
        11,11,11,11,11,11,10,10,10,10,10,10,10,9,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,
        8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
        6,6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};

static int dist1,dist2;

/* initializes the ADC */
void adc_init(void){
	DDRC = 0b0;
        //ADMUX = 0 | _BV(ADLAR); // channel 0, left-justified result
	ADMUX = 0b11000000;
        ADCSRA = _BV(ADEN) | _BV(ADPS0);
	ADCSRA |= _BV(ADSC);
	while (ADCSRA & (1 << ADSC));
	// _BV(bit) == (1 << bit)
}

/* starts an ADC conversion */
void adc_start_conversion(void){
	ADCSRA |= _BV(ADSC);

}

/* returns boolean value indicating if the ADC conversion is still in prgress */
int adc_conversion_in_progress(void){

    return !(ADCSRA & _BV(ADIF));
}

/* clears the ADC interrupt flag */
void adc_clear_interrupt_flag(void)
{
    ADCSRA |= _BV(ADIF);
}

uint8_t calc_avg(uint8_t newval) {
        uint8_t sum = 0;
	
	int i =0;
        for (i=0; i<4; i++) {
                adc_data[i+1] = adc_data[i];
        }

        adc_data[0] = newval;
        for (i=0; i<5; i++) {
                sum += adc_data[i];
        }

        sum = sum/5;
        return sum;
}


/* get ADC Value */
uint8_t get_adc(){

		uint8_t adc_value;        /* sensor ADC value */

                adc_start_conversion();

		while(adc_conversion_in_progress());

		adc_value = ADCH;

		adc_clear_interrupt_flag();

		adc_value = calc_avg(adc_value);

		return(adc_value);
}

int get_avg_adc(){

	
	int sum = 0;
	int avg;
	int i = 0;
	if (sum = 0) {
	while(i < 5){

		adc_data[i] = get_adc();
		sum += adc_data[i];
		i++;
	}
	}

	avg = sum/5;

	//_serial_write((unsigned char)(avg+0x30));

	return avg;
}

int get_distance(int adc_value){

	return sensor_data[adc_value];

}

int get_speed(){

	dist1 = get_distance(get_adc());
	_delay_ms(50);
	dist2 = get_distance(get_adc());

	return (dist2 - dist1)/(50*10^-3);
}

void distance_sensor_print(int adc, int dist){

	char buffer[10];
	//serial_print((unsigned char*)"sensor value : \n\r\0");
	itoa(adc, buffer, 10);
	//serial_print((unsigned char*)buffer);
	//serial_print((unsigned char*)"distance : \n\r\0");
	itoa(dist, buffer, 10);
        //serial_print((unsigned char*)buffer);

}
