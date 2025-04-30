#ifndef __SYS_H
#define __SYS_H

#include "stm32h7r3xx.h"

// 系统时钟配置
void SystemClock_Config(void);

// 中断优先级分组
void NVIC_Config(void);

// 全局变量声明
extern uint32_t SystemCoreClock;

#endif // __SYS_H