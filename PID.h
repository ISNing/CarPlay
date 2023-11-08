#ifndef _PID_H_
#define _PID_H_

struct PID {
    float kp, ki, kd;
};
typedef struct PID _PID;

struct HistoryError {
    float integral_bias, last_bias;
};
typedef struct HistoryError _HistoryError;

signed char PWMMotorL(signed char TraceData/*, float TarSpeed*/);
signed char PWMMotorR(signed char TraceData/*, float TarSpeed*/);

#endif