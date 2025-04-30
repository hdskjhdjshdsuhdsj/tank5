#ifndef __PWM_H__  // 宏保护避免重复包含
#define __PWM_H__

#include "sys.h"
#include "stm32h7rsxx_hal.h"

// 定义用于控制 SG90 舵机的定时器 3 的 PWM 相关参数
// 定时器 3 的 PWM 自动重载值，这里减 1 是因为计数从 0 开始
#define TIM4_PWM_SG90_PERIOD  (72 - 1)
// 定时器 3 的 PWM 预分频器值，同样减 1 是因为计数从 0 开始
#define TIM4_PWM_SG90_PRESCALER (9999 - 1)

// 定义无符号短整型别名 u16，方便代码书写
typedef unsigned short u16;

//// 计算 PWM 频率，根据定时器的自动重载值和预分频器值以及系统时钟频率（假设系统时钟为 72MHz）
//// 公式为：系统时钟频率 / (自动重载值 * 预分频器值)
//#define SG90_PWM_FREQ  72000000 / ((TIM4_PWM_SG90_PERIOD) * (TIM3_PWM_SG90_PRESCALER))

//// 定义 SG90 舵机的中心位置对应的 PWM 脉冲宽度（占定时器周期的比例）
//// 1.5ms 是 SG90 舵机的中心位置，20ms 是一个 PWM 周期，通过比例计算出对应的定时器计数值
//#define SG90_CENTRE   ((int)(1.5 / 20 * TIM4_PWM_SG90_PERIOD))
//// 定义 SG90 舵机右转极限位置对应的 PWM 脉冲宽度（占定时器周期的比例）
//// 0.5ms 是 SG90 舵机右转极限位置，20ms 是一个 PWM 周期，通过比例计算出对应的定时器计数值
//#define SG90_RIGHT    ((int)(0.5 / 20 * TIM4_PWM_SG90_PERIOD))
//// 定义 SG90 舵机左转极限位置对应的 PWM 脉冲宽度（占定时器周期的比例）
//// 2.5ms 是 SG90 舵机左转极限位置，20ms 是一个 PWM 周期，通过比例计算出对应的定时器计数值
//#define SG90_LEFT     ((int)(2.5 / 20 * TIM4_PWM_SG90_PERIOD))

// 函数声明：初始化定时器 3 并使能中断，参数 arr 为自动重载值，psc 为预分频器值
void TIM4_Int_Init(u16 arr, u16 psc);

// 函数声明：初始化定时器 3 以产生用于控制 SG90 舵机的 PWM 信号，参数 arr 为自动重载值，psc 为预分频器值
void TIM4_PWM_SG90_Init(u16 arr, u16 psc);

#endif // __PWM_H__
