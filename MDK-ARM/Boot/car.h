#ifndef __CAR_H__
#define __CAR_H__

#include "stm32h7rsxx_hal.h"

// 以下宏定义用于定义与电机驱动相关的 GPIO 引脚
// PWMA 用于控制电机 A 的 PWM 信号引脚
#define PWMA GPIO_PIN_6
// PWMB 用于控制电机 B 的 PWM 信号引脚
#define PWMB GPIO_PIN_9

// AIN1 和 AIN2 是电机 A 的方向控制引脚
#define AIN1 GPIO_PIN_14
#define AIN2 GPIO_PIN_13

// BIN1 和 BIN2 是电机 B 的方向控制引脚
#define BIN1 GPIO_PIN_15
#define BIN2 GPIO_PIN_12

// 函数声明：初始化定时器 1 的 PWM 功能
// 参数 arr: 定时器自动重载值
// 参数 psc: 定时器预分频器值
void TIM4_PWM_Init(uint16_t arr, uint16_t psc);

// 函数声明：初始化 TB6612 电机驱动芯片相关的 GPIO 引脚
void TB6612_GPIO_Init(void);

// 函数声明：控制小车前进
void go_straight(void);

// 函数声明：控制小车左转
void turn_left(void);

// 函数声明：控制小车后退
void go_back(void);

// 函数声明：控制小车右转
void turn_right(void);

// 函数声明：控制小车停止
void stop(void);

//void set_motor_speed(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t pulse);
#endif // __CAR_H__