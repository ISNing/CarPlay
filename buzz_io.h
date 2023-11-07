#ifndef _BUZZ_IO_H_
#define _BUZZ_IO_H_
#include <Atmel/AT89X52.H>

// 0: On 1: Off
#define BUZZ P2_3

#define BuzzOn BUZZ = 0
#define BuzzOff BUZZ = 1
#endif