#ifndef _PID_H_
#define _PID_H_

struct PID {
    int kp, ki, kd;
};
typedef struct PID _PID;

struct HistoryError {
    int integral_bias, last_bias;
};
typedef struct HistoryError _HistoryError;

signed char PWMMotorL();
signed char PWMMotorR();
void CalcTurnPwm(signed char TraceData);

#define CalcWithPID(res, bias, pid, his)                                       \
    his.integral_bias += bias;                                                 \
    res = pid.kp * bias + pid.ki * his.integral_bias +                         \
          pid.kd * (bias - his.last_bias);                                     \
    his.last_bias = bias;

#define DEF_PWM_L 10
#define DEF_PWM_R 10
#define TURN_KP 3
#define TURN_KI 0
#define TURN_KD 0

#endif