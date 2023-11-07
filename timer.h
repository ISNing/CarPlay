#ifndef _TIMER_H_
#define _TIMER_H_
#include <Atmel/AT89X52.H>

#define FOSC 12000000L
#define Times (65536 - FOSC / 12) // 1us

void check_reset();
void delay_us(unsigned short us);
void delay_ms(unsigned long ms);
void timer_reset();

#endif