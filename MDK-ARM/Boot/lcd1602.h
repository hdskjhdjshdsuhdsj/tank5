#ifndef __LCD1602_H
#define __LCD1602_H

#include "main.h"

void LCD1602_Init(void);
void LCD1602_WriteCommand(uint8_t cmd);
void LCD1602_WriteData(uint8_t data);

#endif /* __LCD1602_H */