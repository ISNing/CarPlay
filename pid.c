#include "pid.h"

// 定义转向pid参数结构体
_PID TurnPdate = {100, 0, -34};

// 定义速度pid参数结构体
_PID SpdPdate = {-50, -6, 0};

/*@brief: 位置式PID控制器
 * @param:
 *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */
int PositionPID(float deviation, _PID pid) {
    float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd;
    float xdata Bias, Pwm, Integral_bias, Last_Bias;
    Bias = deviation;      // 计算偏差
    Integral_bias += Bias; // 求出偏差的积分
    Pwm = Position_KP * Bias + Position_KI * Integral_bias +
          Position_KD * (Bias - Last_Bias); // 位置式PID控制器
    Last_Bias = Bias;                       // 保存上一次偏差
    return Pwm;
}

/* @brief: 为速度pid使用位置式PID控制器，对积分值进行限幅
 * @param:
 *        [in] float deviation: 和目标值的偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */
int PositionPIDToSpd(float deviation, _PID pid) {
    float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd;
    static float xdata Bias, Pwm, Integral_bias, Last_Bias, pwmKI = 0;
    Bias = deviation;      // 计算偏差
    Integral_bias += Bias; // 求出偏差的积分
    pwmKI = Position_KI * Integral_bias;
    if (pwmKI > MAX_MOTOR_PWM)
        Integral_bias = MAX_MOTOR_PWM / Position_KI;
    Pwm = Position_KP * Bias + pwmKI +
          Position_KD * (Bias - Last_Bias); // 位置式PID控制器
    Last_Bias = Bias;                       // 保存上一次偏差
    return Pwm;
}
