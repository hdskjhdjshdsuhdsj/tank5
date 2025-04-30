#include "delay.h"
volatile uint32_t fac_us = 0;  // 用于微秒延时的系数
volatile uint32_t fac_ms = 0;  // 用于毫秒延时的系数
void delay_us(uint32_t us)
{
    uint32_t i;
    for (i = 0; i < us * (SystemCoreClock / 1000000); i++)  // 根据系统时钟频率调整
    {
        __NOP();  // 执行空操作以消耗时间
    }
}

void delay_ms(uint32_t ms)
{
    HAL_Delay(ms);  // 使用 HAL 库的延时函数
}
void delay_init(void)
{
    // 配置SysTick时钟源为HCLK/8
		HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);  // 配置 SysTick 为 1ms 中断
		HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);  // 设置时钟源为 HCLK/8
    fac_us = SystemCoreClock / 8000000;  // 计算1us对应的SysTick计数值
    fac_ms = fac_us * 1000;              // 计算1ms对应的SysTick计数值
}