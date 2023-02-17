/*
 * DEFINES.h
 *
 * Created: 04/02/2023 03:37:14 p. m.
 *  Author: Johan Lee
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

	#include <avr/io.h>
	#define __watchdog_reset()  asm("wdr")
	#define ALARM_PIN			PORTD4
	#define MIN_VALUE			100

#endif /* DEFINES_H_ */