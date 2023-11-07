#ifndef _MOTOR_IO_H_
#define _MOTOR_IO_H_
#include <Atmel/AT89X52.H>

#define MOTOR_IN1 P1_2;
#define MOTOR_IN2 P1_3;
#define MOTOR_IN3 P1_6;
#define MOTOR_IN4 P1_7;
#define MOTOR_EN1 P1_4;
#define MOTOR_EN2 P1_5;

#define Motor1Go                                                               \
    { P1_2 = 0, P1_3 = 1; }
#define Motor1Back                                                             \
    { P1_2 = 1, P1_3 = 0; }
#define Motor1Start                                                            \
    { P1_5 = 1; }
#define Motor1Stop                                                             \
    { P1_5 = 0; }
#define Motor2Go                                                               \
    { P1_6 = 1, P1_7 = 0; }
#define Motor2Back                                                             \
    { P1_6 = 0, P1_7 = 1; }
#define Motor2Start                                                            \
    { P1_4 = 1; }
#define Motor2Stop                                                             \
    { P1_4 = 0; }

#endif