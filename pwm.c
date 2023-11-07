#include "pwm.h"

signed int pwm_motor1 = 0;
signed int pwm_motor2 = 0;

// 0: Stop 1: Run
bit motor1_go = 0;
bit motor2_go = 0;

signed int pwm_count_motor1 = 0;
signed int pwm_count_motor2 = 0;

int pwm_restricted(int val) {
    if (val > MAX_MOTOR_PWM)
        return MAX_MOTOR_PWM;
    else if (val < -MAX_MOTOR_PWM)
        return -MAX_MOTOR_PWM;
    else
        return val;
}

void set_pwm_motor1(int val) { pwm_motor1 = pwm_restricted(val); }

void set_pwm_motor2(int val) { pwm_motor2 = pwm_restricted(val); }

int get_pwm_motor1() { return pwm_motor1; }

int get_pwm_motor2() { return pwm_motor2; }

void PwmMotor1Refresh(void) {
    pwm_count_motor1++;
    if (pwm_motor1 < 0) {
        Motor1Back;
    } else {
        Motor1Go;
    }
    if (motor1_go) {
        if (pwm_count_motor1 <= abs(pwm_motor1)) {
            Motor1Start;

        } else {
            Motor1Stop;
        }
        if (pwm_count_motor1 >= MAX_MOTOR_PWM)
            pwm_count_motor1 = 0;
    } else {
        Motor1Stop;
    }
}

void PwmMotor2Refresh(void) {
    pwm_count_motor2++;
    if (pwm_motor2 < 0) {
        Motor2Back;
    } else {
        Motor2Go;
    }
    if (motor2_go) {
        if (pwm_count_motor2 <= abs(pwm_motor2)) {
            Motor2Start;

        } else {
            Motor2Stop;
        }
        if (pwm_count_motor2 >= MAX_MOTOR_PWM)
            pwm_count_motor2 = 0;
    } else {
        Motor2Stop;
    }
}

void PwmRefreshBlocked(bit (*stop_check_ptr)()) {
    motor1_go = 1;
    motor1_go = 1;
    while (1) {
        PwmMotor1Refresh();
        PwmMotor2Refresh();
        delay_us(1000000 / MOTOR_PWM_FREQ);
        if (stop_check_ptr())
            break;
    }
    motor1_go = 0;
    motor1_go = 0;
}
