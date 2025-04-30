#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32h7rsxx_hal.h"
#include "main.h"
// 声明延时函数
void delay_ms(uint32_t ms);  // 毫秒级延时
void delay_us(uint32_t us);  // 微秒级延时
void delay_init(void);
void delay_ms(uint32_t ms);
#endif // __DELAY_H__