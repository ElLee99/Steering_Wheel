/*
 * Steering_Wheel_Load_Cell.c
 *
 * Created: 03/02/2023 08:14:48 p. m.
 * Author : Johan Lee
 */ 

#ifndef F_CPU
	#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <DEFINES.h>


void WDT_init(void){
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		__watchdog_reset();														/*Reset Watchdog Timer*/
		WDTCSR |= (1<<WDCE) | (1<<WDE);											/*Watchdog Change Enable and Watchdog System Reset Enable, necessary to change the prescaler*/
		WDTCSR  = (1<<WDIE) | (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);		/* Watchdog System Reset Enable, Watchdog Interrupt Enable, Changes Time-Out to 2 seconds*/
	}																			/*Goes to WDT Interruption before reset*/
}


void GPIO_init(void){
	DDRD |= (1<<ALARM_PIN);							/*Set ALARMA_PIN as Output*/
}


void ADC_Init_CHO(void){
	
	DDRC &= ~(1<<PORTC0);							/*Input with...*/
	PORTC &= ~(1<<PORTC0);							/*..Tri-state (Hi-Z)*/
	
	DIDR0 = (1<<ADC0D);								/* Digital Input Disable*/
	
	ADMUX =  (1<<REFS0);							/* Voltage Reference Selections, AVCC with external capacitor at AREF pin*/
													/*Analog Channel 0 by Default*/
					
	ADCSRA = (1<<ADEN);								/* ADC Enable*/
	ADCSRA |= (1<<ADATE);							/* ADC Auto Trigger Enable*/
	ADCSRA |= (1<<ADIE);							/* ADC Interrupt Enable*/
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);	/*ADC Prescaler Select 128*/
	ADCSRA |= (1<<ADSC);							/*ADC Start Conversion*/
	
}

ISR(WDT_vect){
	/*Escribir funcion de que hacer en 
	caso de que el watchdog expire, antes de resetear*/
}

ISR(ADC_vect){
	if (ADC <= MIN_VALUE) {PORTD |= (1<<ALARM_PIN);}
	else{PORTD &= ~(1<<ALARM_PIN);}
	__watchdog_reset();
}

int main(void)
{
	GPIO_init();
	ADC_Init_CHO();
	WDT_init();
	sei();
	
    while (1) 
    {

    }
}

