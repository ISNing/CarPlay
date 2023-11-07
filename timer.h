#ifndef _TIMER_H_
#define _TIMER_H_
#include <Atmel/AT89X52.H>
/**
TIME_PER_INTERRUPT_NS = (65536 - TIMER_INIT)*1e6/(FOSC/12)
TIMER_INIT = 65536 - TIME_PER_INTERRUPT_NS*(FOSC/12)/1e9
And TIMER_INIT < 65536 as well as TIME_PER_INTERRUPT_NS > 1 (1.09)
*/
#define FOSC 12e6L
#define TIME_PER_INTERRUPT_US 1e3 // > 1
#define TIMER_INIT (int)(65536 - TIME_PER_INTERRUPT_US * (FOSC/12)/1e9)

void delay_5us();
void delay_10us();
void delay_ms(unsigned long ms);
void delay_10ms();
void delay_200ms();
void delay_500ms();
void delay_1s();

#endif