#ifndef _PWM_H_
#define _PWM_H_
#include <math.h>
#include "motor_io.h"
#include "delay.h"

#define MOTOR_PWM_FREQ 2500
#define MAX_MOTOR_PWM 40

void set_pwm_motor1(int val);
void set_pwm_motor2(int val);
int get_pwm_motor1();
int get_pwm_motor2();
void PwmMotor1Refresh(void);
void PwmMotor2Refresh(void);
void PwmRefreshBlocked(bit (*stop_check_ptr)());

#endif