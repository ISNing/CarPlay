#ifndef _PID_H_
#define _PID_H_
#include "pwm.h"

struct PID {
    float kp;
    float ki;
    float kd;
};
typedef struct PID _PID;

int PositionPID(float deviation, _PID pid);
int PositionPIDToSpd(float deviation, _PID pid);

#endif