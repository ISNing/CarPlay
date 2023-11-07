#include <Atmel/AT89X52.H>
#include <math.h>

#ifndef _LED_H_
#define _LED_H_

// 时钟频率
#define FOSC 12000000L
// 计算器初值计算
#define Times (65536 - FOSC / 12) // 1us

#define MAX_MOTOR_PWM 1000000

// 定义小车驱动模块输入IO口
sbit IN1 = P1 ^ 2;
sbit IN2 = P1 ^ 3;
sbit IN3 = P1 ^ 6;
sbit IN4 = P1 ^ 7;
sbit EN1 = P1 ^ 4;
sbit EN2 = P1 ^ 5;

// 蜂鸣器接线定义
sbit BUZZ = P2 ^ 3;

#define Left_1_led P3_3  // 左传感器
#define Right_1_led P3_2 // 右传感器

#define motor1_sig P1_5
#define motor2_sig P1_4

#define Left_moto_go                                                           \
    { P1_2 = 0, P1_3 = 1; } // 左电机向前走
#define Left_moto_back                                                         \
    { P1_2 = 1, P1_3 = 0; } // 左边电机向后转
#define Left_moto_Stop                                                         \
    { P1_5 = 0; } // 左边电机停转
#define Right_moto_go                                                          \
    { P1_6 = 1, P1_7 = 0; } // 右边电机向前走
#define Right_moto_back                                                        \
    { P1_6 = 0, P1_7 = 1; } // 右边电机向后走
#define Right_moto_Stop                                                        \
    { P1_4 = 0; } // 右边电机停转

signed int pwm_motor1 = 0;
signed int pwm_motor2 = 0;

void set_pwm_motor1(int val) { pwm_motor1 = val; }

void set_pwm_motor2(int val) { pwm_motor2 = val; }

// 0: 停止 1: 运行
bit Right_moto_stop = 1;
bit Left_moto_stop = 1;

unsigned long time_us = 0;

// 延时函数
void delay(unsigned int k) {
    unsigned int x, y;
    for (x = 0; x < k; x++)
        for (y = 0; y < 2000; y++)
            ;
}
void delay_us(unsigned int us) {
    unsigned int x;
    for (x = 0; x < us; x++)
        ;
}
void delay_ms(unsigned int ms) {
    unsigned int x;
    for (x = 0; x < ms; x++)
        delay_us(1000);
}

// 前进
void run(void) {
    pwm_motor1 = 500000; // 速度调节变量 0-20。。。0最小，20最大
    pwm_motor2 = 500000;
    Left_moto_go;  // 左电机往前走
    Right_moto_go; // 右电机往前走
}

// 左转
void leftrun(void) {
    pwm_motor1 = 10;
    pwm_motor2 = 10;
    Right_moto_go;  // 右电机往前走
    Left_moto_back; // 左电机后走
}

// 右转
void rightrun(void) {
    pwm_motor1 = 10;
    pwm_motor2 = 10;
    Left_moto_go;    // 左电机往前走
    Right_moto_back; // 右电机往后走
}

// 停止
void stop(void) {
    Right_moto_Stop;
    Left_moto_Stop;
}

/*************************************************************************************************/
/*----------------------------------------可修改片段---------------------------------------------*/
/*************************************************************************************************/
signed int pwm_count_motor1 = 0;
signed int pwm_count_motor2 = 0;

/************************************************************************/
/*                    PWM调制电机转速                                   */
/************************************************************************/
/*                    左电机调速                                        */
void PwmMotor1Refresh(void) {
    if (pwm_motor1 < 0) {
        Left_moto_back;
    } else {
        Left_moto_go;
    }
    if (Left_moto_stop) {
        if (pwm_count_motor1 <= abs(pwm_motor1)) {
            motor1_sig = 1;

        } else {
            motor1_sig = 0;
        }
        if (pwm_count_motor1 >= MAX_MOTOR_PWM)
            pwm_count_motor1 = 0;
    } else {
        motor1_sig = 0;
    }
}
/******************************************************************/
/*                    右电机调速                                  */
void PwmMotor2Refresh(void) {
    if (pwm_motor2 < 0) {
        Right_moto_back;
    } else {
        Right_moto_go;
    }
    if (Right_moto_stop) {
        if (pwm_count_motor2 <= abs(pwm_motor2)) {
            motor2_sig = 1;

        } else {
            motor2_sig = 0;
        }
        if (pwm_count_motor2 >= MAX_MOTOR_PWM)
            pwm_count_motor2 = 0;
    } else {
        motor2_sig = 0;
    }
}

/***************************************************/
///*TIMER0中断服务子函数产生PWM信号*/
void timer0() interrupt 1 using 2 {
    // 给T0低字节装载初始值
    TL0 = (char)Times;
    // 给T0高字节装载初始值
    TH0 = (char)(Times >> 8);

    time_us++;

    pwm_count_motor1++;
    PwmMotor1Refresh();

    pwm_count_motor2++;
    PwmMotor2Refresh();
}

/*********************************************************************/

#endif