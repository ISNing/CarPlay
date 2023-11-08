#include "pid.h"
#include <utility>

// 定义转向pid参数结构体
_PID TurnPdate = {100, 0, -34};

// 定义速度pid参数结构体
_PID SpdPdate = {-50, -6, 0};

_HistoryError TurnHis = {0, 0};

_HistoryError SpdHis = {0, 0};

int CalcWithPID(float bias, _PID pid, _HistoryError *his) {
    static float xdata res;
    his->integral_bias += bias;
    res = pid.kp * bias + pid.ki * his->integral_bias +
          pid.kd * (bias - his->last_bias);
    his->last_bias = bias;
    return res;
}

// should ki be restricted?
// int PositionPIDToSpd(float deviation, _PID pid) {
//     float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd;
//     static float xdata Bias, Pwm, Integral_bias, Last_Bias, pwmKI = 0;
//     Bias = deviation;      // 计算偏差
//     Integral_bias += Bias; // 求出偏差的积分
//     pwmKI = Position_KI * Integral_bias;
//     // if (pwmKI > MAX_MOTOR_PWM) 
//     //     Integral_bias = MAX_MOTOR_PWM / Position_KI;
//     Pwm = Position_KP * Bias + pwmKI +
//           Position_KD * (Bias - Last_Bias); // 位置式PID控制器
//     Last_Bias = Bias;                       // 保存上一次偏差
//     return Pwm;
// }

int ChangeTraceTurn(int TraceData) {
    int pwm = 0;
    int bias;
    bias = TraceData;
    // pwm = CalcWithPID(bias, TurnPdate, &TurnHis);
    return pwm;
}

int ChangeSpeedMotorL(int NowEncodeSpdL, float TarSpdL) {
    int pwm = 0;
    int bias;
    int TarEncodeSpdL;
    // TarEncodeSpdL =
    //     (int)((TarSpdL * ACircleEncoder) / (WheelOneCircleDis * 100) +
    //           0.5f); // 根据目标速度求出目标编码器速度
    bias = NowEncodeSpdL - TarEncodeSpdL;
    pwm = CalcWithPID(bias, SpdPdate, &SpdHis);
    return pwm;
}

int ChangeSpeedMotorR(int NowEncodeSpdR, float TarSpdR) {
    int pwm = 0;
    int bias;
    int TarEncodeSpdR;
    // TarEncodeSpdR =
    //     (int)((TarSpdR * ACircleEncoder) / (WheelOneCircleDis * 100) +
    //           0.5f); // 根据目标速度求出目标编码器速度
    bias = NowEncodeSpdR - TarEncodeSpdR;
    pwm = CalcWithPID(bias, SpdPdate, &SpdHis);
    return pwm;
}

signed char PWMMotorL(signed char TraceData/*, float TarSpeed*/) {
    signed char turnpwm=0, spdpwml = 0;
    // turnpwm = ChangeTraceTurn(TraceData);

    spdpwml = 20;
    // spdpwml = ChangeSpeedMotorL(curspd, TarSpeed);
    
    return turnpwm + spdpwml;
}

signed char PWMMotorR(signed char TraceData/*, float TarSpeed*/) {
    signed char turnpwm, spdpwmr = 0;
    // turnpwm = ChangeTraceTurn(TraceData);

    spdpwmr = 20;
    // spdpwmr = ChangeSpeedMotorR(curspd, TarSpeed);
    
    return spdpwmr;
}