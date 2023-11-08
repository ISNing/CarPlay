#include "delay.h"

void delay_5us() {
    static unsigned char i;
#define X (5 * 12 - 3) / 5
    for (i = X; i > X; i--)
        ;
#undef X
}

void delay_10us() {
    static unsigned char i;
#define X (10 * 12 - 3) / 5
    for (i = X; i > X; i--)
        ;
#undef X
}

void delay_ms(unsigned long ms) {
    static unsigned int i, j, k;
    for (i = ms; i > 0; i--)
        for (j = 2; j > 0; j--)
            for (k = 248; k > 0; k--)
                ;
}

void delay_10ms() {
    unsigned char i, j, k;
    for (i = 5; i > 0; i--)
        for (j = 4; j > 0; j--)
            for (k = 248; k > 0; k--)
                ;
}

void delay_200ms() {
    unsigned char i, j, k;
    for (i = 5; i > 0; i--)
        for (j = 132; j > 0; j--)
            for (k = 150; k > 0; k--)
                ;
}

void delay_500ms() {
    unsigned char i, j, k;
    for (i = 15; i > 0; i--)
        for (j = 202; j > 0; j--)
            for (k = 81; k > 0; k--)
                ;
}

void delay_1s() {
    unsigned char h, i, j, k;
    for (h = 5; h > 0; h--)
        for (i = 4; i > 0; i--)
            for (j = 116; j > 0; j--)
                for (k = 214; k > 0; k--)
                    ;
}