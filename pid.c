#include "pid.h"

// 定义转向pid参数结构体
_PID TurnPID = {TURN_KP, TURN_KI, TURN_KD};

// 定义速度pid参数结构体
// xdata _PID SpdPID = {15, -3, 0};

_HistoryError TurnHis = {0, 0};

// xdata _HistoryError SpdHis = {0, 0};
static signed char turn_pwm = 0;

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

void CalcTurnPwm(signed char TraceData) {
    CalcWithPID(turn_pwm, TraceData, TurnPID, TurnHis);
}

// int ChangeSpeedMotorL(int NowEncodeSpdL, float TarSpdL) {
//     idata signed char pwm = 0;
//     idata signed char bias;
//     idata signed char TarEncodeSpdL;
//     // TarEncodeSpdL =
//     //     (int)((TarSpdL * ACircleEncoder) / (WheelOneCircleDis * 100) +
//     //           0.5f); // 根据目标速度求出目标编码器速度
//     bias = NowEncodeSpdL - TarEncodeSpdL;
//     pwm = CalcWithPID(bias, &SpdPID, &SpdHis);
//     return pwm;
// }

// int ChangeSpeedMotorR(int NowEncodeSpdR, float TarSpdR) {
//     idata signed char pwm = 0;
//     idata signed char bias;
//     idata signed char TarEncodeSpdR;
//     // TarEncodeSpdR =
//     //     (int)((TarSpdR * ACircleEncoder) / (WheelOneCircleDis * 100) +
//     //           0.5f); // 根据目标速度求出目标编码器速度
//     bias = NowEncodeSpdR - TarEncodeSpdR;
//     pwm = CalcWithPID(bias, &SpdPID, &SpdHis);
//     return pwm;
// }

signed char PWMMotorL() { return DEF_PWM_L + turn_pwm; }

signed char PWMMotorR() { return DEF_PWM_R - turn_pwm; }