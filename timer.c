#include "timer.h"

unsigned char time_lock = 0;
unsigned long time_hns = 0;

void check_reset() {
    if (time_lock == 0) {
        time_hns = 0; // reset to 0
    }
}

void delay_hns(unsigned short hns) {
    long init = time_hns;
    check_reset();
    time_lock++;
    while ((time_hns - init) < hns)
        ;
    time_lock--;
    check_reset();
}

void delay_us(unsigned short us) {
    delay_hns(10 * us);
}

void delay_ms(unsigned long ms) {
    unsigned long x;
    for (x = 0; x < ms; x++)
        delay_us(1000);
}

void timer_reset() {
    TL0 = (char)TIMER_INIT;
    TH0 = (char)(TIMER_INIT >> 8);
}

void timer0() interrupt 1 using 2 {
    timer_reset();
    if (time_lock) {
        time_hns++;
    }
}
