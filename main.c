#include "pwm.h"
#include "timer.h"
#include "buzz_io.h"

bit stop_check() { return 1; }

int main(void) {

    unsigned short i;
    P1 = 0X00; // 关电机
begin:
    for (i = 0; i < 50; i++) {
        delay_ms(1);
        if (P3_7 != 0) // K4 not pressed
            goto begin;
    }

    BuzzOn;
    delay_ms(50);
    BuzzOff;

    // Do not modify this snippet
    timer_reset();
    TMOD = 0X01;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
    // End of snippet

    // Full speed
    set_pwm_motor1(MAX_MOTOR_PWM);
    set_pwm_motor2(MAX_MOTOR_PWM);

    PwmRefreshBlocked(stop_check);

    goto begin;
}