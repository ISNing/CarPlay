#include "buzz_io.h"
#include "delay.h"
#include "led_sensor.h"
#include "pid.h"
#include "pwm.h"

bit bias_ignored = 0;
bit k2_pressed = 0;
bit k3_pressed = 0;
bit last_left_led = 0;
bit last_right_led = 0;

bit stop_check() {
    signed char turn_bias = 0;
    static int pwml = 0, pwmr = 0;
    if (Left_1_led == 0) {
        last_left_led = 0;
        turn_bias++;
    } else last_left_led = 1;
    if (Right_1_led == 0) {
        last_right_led = 0;
        turn_bias--;
    } else last_right_led = 1;

    CalcTurnPwm(turn_bias);
    pwml = PWMMotorL();//bias_ignored ? 0 : 
    pwmr = PWMMotorR();

    set_pwm_motor1(pwml);
    set_pwm_motor2(pwmr);
    if (P3_5 == 0) { // K2 pressed
        BuzzOn;
        k2_pressed = 1;
    } else {
        if (k2_pressed) {
            BuzzOff;
            bias_ignored = 1;
            // set_pwm_motor1(get_pwm_motor1() + 1);
            // set_pwm_motor2(get_pwm_motor2() + 1);
        }
        k2_pressed = 0;
    }
    if (P3_6 == 0) { // K3 pressed
        BuzzOn;
        k3_pressed = 1;
    } else {
        if (k3_pressed) {
            BuzzOff;
            bias_ignored = 0;
            // set_pwm_motor1(get_pwm_motor1() - 1);
            // set_pwm_motor2(get_pwm_motor2() - 1);
        }
        k3_pressed = 0;
    }
    if (P3_7 == 0) // K4 pressed
        return 1;
    else
        return 0;
}

int main(void) {

    unsigned short i;
    P1 = 0X00; // 关电机

begin:
    for (i = 0; i < 50; i++) {
        delay_ms(1);
        if (P3_4 != 0) // K1 not pressed
            goto begin;
    }

    BuzzOn;
    delay_ms(50);
    BuzzOff;

    set_pwm_motor1(0);
    set_pwm_motor2(0);

    PwmRefreshBlocked(stop_check);

    goto begin;
}
