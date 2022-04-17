/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : eeprom.h
  * @brief          : Header for eeprom.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stdint.h"
#include "stm32f0xx_hal.h"

void EEPROM_Write(uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);

void EEPROM_Read(uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);

void EEPROM_Page_Erease(uint16_t page);





#endif /* INC_EEPROM_H_ */



