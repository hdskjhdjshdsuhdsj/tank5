#include "car.h"
#include "stm32h7rsxx_hal.h"

// 定义定时器句柄和 PWM 参数
extern TIM_HandleTypeDef htim4;

// 初始化TB6612电机控制GPIO引脚
void TB6612_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIO时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // 初始化电机A的方向控制引脚
    GPIO_InitStruct.Pin = AIN1 | AIN2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 初始化电机B的方向控制引脚
    GPIO_InitStruct.Pin = BIN1 | BIN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// 设置电机速度（通过PWM占空比）
//void set_motor_speed(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t pulse)
//{
//    // 设置指定通道的PWM占空比
//    __HAL_TIM_SET_COMPARE(htim4, 1, pulse);
//}

// 控制小车前进
void go_straight(void)
{
    // 电机A前进：AIN1高，AIN2低
    HAL_GPIO_WritePin(GPIOB, AIN1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, AIN2, GPIO_PIN_RESET);

    // 电机B前进：BIN1高，BIN2低
    HAL_GPIO_WritePin(GPIOB, BIN1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, BIN2, GPIO_PIN_RESET);
    
    // 启动电机PWM
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 5000);  // 例如设置PWM占空比为50%
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 5000);  // 例如设置PWM占空比为50%
}

// 控制小车后退
void go_back(void)
{
    // 电机A后退：AIN1低，AIN2高
    HAL_GPIO_WritePin(GPIOC, AIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, AIN2, GPIO_PIN_SET);

    // 电机B后退：BIN1低，BIN2高
    HAL_GPIO_WritePin(GPIOB, BIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, BIN2, GPIO_PIN_SET);
    
    // 启动电机PWM
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 1500);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 1500);
}

// 控制小车停止
void stop(void)
{
    // 停止电机A：AIN1低，AIN2低
    HAL_GPIO_WritePin(GPIOC, AIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, AIN2, GPIO_PIN_RESET);

    // 停止电机B：BIN1低，BIN2低
    HAL_GPIO_WritePin(GPIOB, BIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, BIN2, GPIO_PIN_RESET);
    
    // 关闭PWM输出
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);  // 设置占空比为0，停止电机
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);  // 设置占空比为0，停止电机
}

// 控制小车左转
void turn_left(void)
{
    // 电机A前进：AIN1高，AIN2低
    HAL_GPIO_WritePin(GPIOC, AIN1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, AIN2, GPIO_PIN_RESET);

    // 电机B后退：BIN1低，BIN2高
    HAL_GPIO_WritePin(GPIOB, BIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, BIN2, GPIO_PIN_SET);
    
    // 启动电机PWM
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 5000);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 5000);
}

// 控制小车右转
void turn_right(void)
{
    // 电机A后退：AIN1低，AIN2高
    HAL_GPIO_WritePin(GPIOC, AIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, AIN2, GPIO_PIN_SET);

    // 电机B前进：BIN1高，BIN2低
    HAL_GPIO_WritePin(GPIOB, BIN1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, BIN2, GPIO_PIN_RESET);
    
    // 启动电机PWM
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 5000);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 5000);
}
