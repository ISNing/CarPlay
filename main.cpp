#include "CarPlay_PWM.h"
#include "PID.cpp"

// 主函数
int main(void) {

    unsigned short i;
    P1 = 0X00; // 关电机
B:
    for (i = 0; i < 50; i++) // 判断K4是否按下
    {
        delay(1); // 1ms内判断50次，如果其中有一次被判断到K4没按下，便重新检测
        if (P3_7 !=
            0) // 当K4按下时，启动小车前进，如有不明，请看慧净51单片机视频教程
            goto B; // 跳转到标号B，重新检测
    }

    BUZZ = 0; // 50次检测K4确认是按下之后，蜂鸣器发出“滴”声响，然后启动小车。
    delay(50);
    BUZZ = 1; // 响50ms后关闭蜂鸣器

    // Do not modify this snippet
    TMOD = 0X01;
    TH0 = 0X00; // 1ms定时
    TL0 = 0X18;
    TR0 = 1;
    ET0 = 1;
    EA = 1; // 开总中断
    // End of snippet

    while (1) // 无限循环
    {

        // 有信号为0  没有信号为1
        // if (Left_1_led == 0 && Right_1_led == 0)

        // run(); // 调用前进函数

        // else {
        //     if (Left_1_led == 1 && Right_1_led == 0) // 左边检测到黑线
        //     {
        //         leftrun(); // 调用小车左转  函数
        //     }

        //     if (Right_1_led == 1 && Left_1_led == 0) // 右边检测到黑线
        //     {
        //         rightrun(); // 调用小车右转	函数
        //     }
        // }
    }
}