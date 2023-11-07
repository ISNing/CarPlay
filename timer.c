#include "timer.h"

unsigned char time_lock = 0;
unsigned long time_us = 0;

void check_reset() {
    if (time_lock == 0) {
        time_us = 0; // reset to 0
    }
}

void delay_us(unsigned short us) {
    long init = time_us;
    check_reset();
    time_lock++;
    while ((time_us - init) < us)
        ;
    time_lock--;
    check_reset();
}
void delay_ms(unsigned long ms) {
    unsigned long x;
    for (x = 0; x < ms; x++)
        delay_us(1000);
}

void timer_reset() {
    TL0 = (char)Times;
    TH0 = (char)(Times >> 8);
}

void timer0() interrupt 1 using 2 {
    timer_reset();
    if (time_lock) {
        time_us++;
    }
}
