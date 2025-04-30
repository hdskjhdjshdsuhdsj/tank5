#include "pwm.h"
#include "stm32h7rsxx_hal.h"
#include "main.h"  // 确保可以调用 main.c 中的 Error_Handler

// 定义定时器句柄
extern TIM_HandleTypeDef htim4;

// TIM3 PWM部分初始化
// PWM输出初始化：arr为自动重装载值，psc为时钟预分频数
//void TIM4_PWM_SG90_Init(uint16_t arr, uint16_t psc)
//{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    TIM_OC_InitTypeDef sConfigOC = {0};

//    __HAL_RCC_TIM4_CLK_ENABLE();

//    // 使能GPIOB时钟
//    __HAL_RCC_GPIOB_CLK_ENABLE();

//    // 初始化GPIO：配置为PWM输出引脚（GPIOB.5，TIM3 CH2）
//    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_9;  // TIM3 CH2
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // 复用推挽输出
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4; // 配置为TIM3复用功能
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//    // 初始化TIM3，配置为PWM输出模式
//    htim4.Instance = TIM4;
//    htim4.Init.Prescaler = psc;  // 设置预分频器
//    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
//    htim4.Init.Period = arr;  // 设置自动重载值
//    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

//    if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
//    {
//        // 初始化失败时调用 main.c 中的 Error_Handler()
//        Error_Handler();
//    }

//    // 配置PWM输出的模式和占空比
//    sConfigOC.OCMode = TIM_OCMODE_PWM1;  // 选择PWM模式2
//    sConfigOC.Pulse = 0;  // 初始占空比为0
//    sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;  // 输出极性：低电平有效
//    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;  // 禁用快速模式

//    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
//    {
//        // 配置失败时调用 main.c 中的 Error_Handler()
//        Error_Handler();
//    }

//    // 使能输出比较预装载寄存器
//    __HAL_TIM_ENABLE_OCxPRELOAD(&htim4, TIM_CHANNEL_1);

//    // 启动PWM输出
//    if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1) != HAL_OK)
//    {
//        // 启动失败时调用 main.c 中的 Error_Handler()
//        Error_Handler();
//    }
//}

// 动态设置PWM占空比（控制电机速度）
void set_pwm_duty_cycle(uint32_t channel, uint16_t pulse)
{
    if (pulse > TIM4->ARR)  // 检查占空比是否超出最大值
    {
        pulse = TIM4->ARR;  // 限制占空比在最大范围内
    }

    // 设置指定通道的占空比
    __HAL_TIM_SET_COMPARE(&htim4, channel, pulse);
}

// 停止PWM输出
void stop_pwm(void)
{
    // 停止PWM输出
    if (HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1) != HAL_OK)
    {
        // 停止失败时调用 main.c 中的 Error_Handler()
        Error_Handler();
    }
}
