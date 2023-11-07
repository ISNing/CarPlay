#ifndef _PID_H_
#define _PID_H_
// 定义pid结构体
struct PID {
    float kp;
    float ki;
    float kd;
};
typedef struct PID _PID;
#endif