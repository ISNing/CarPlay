#ifndef _TIMER_H_
#define _TIMER_H_
#include <Atmel/AT89X52.H>
/**
TIME_PER_INTERRUPT_NS = (65536 - TIMER_INIT)*1e9/FOSC
TIMER_INIT = 65536 - TIME_PER_INTERRUPT_NS*FOSC/1e9
And TIMER_INIT < 65536 as well as TIME_PER_INTERRUPT_NS > 83.33(84)
*/
#define FOSC 12e6L
#define TIME_PER_INTERRUPT_NS 1e3 // > 83.33(84)
#define TIMER_INIT (int)(65536 - TIME_PER_INTERRUPT_NS * FOSC/1e9)

void check_reset();
void delay_us(unsigned short us);
void delay_ms(unsigned long ms);
void timer_reset();

#endif