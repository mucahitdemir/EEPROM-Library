/*
 * eeprom.c
 *
 *  Created on: Feb 4, 2022
 *      Author: Muco
 */
#include "eeprom.h"
#include "math.h"
#include "string.h"
#include "main.h"


//Extern the I2C handle variable
extern I2C_HandleTypeDef hi2c1;

#define EEPROM_I2C &hi2c1

//Define the address of EEPROM
#define EEPROM_ADDR 0xA0

//Define the page size and number of pages in EEPROM

//#define M24M01

#define M24512

//#define M24256

#ifdef M24512
#define PAGE_SIZE 						128
#define EEPROM_DATA_SIZE 				512
#define PAGE_NUMBER 					(EEPROM_DATA_SIZE/PAGE_SIZE)
#endif

/*    In further implementations, MACROs defined below will be used.   7th Feb, 2022
 *
#ifdef M24256
#define PAGE_SIZE 						64
#define EEPROM_DATA_SIZE 				256
#define PAGE_NUMBER 					(EEPROM_DATA_SIZE/PAGE_SIZE)
#endif

*/
#ifdef M24256
#define PAGE_SIZE 						64
#define EEPROM_DATA_SIZE 				256
#define PAGE_NUMBER 					(EEPROM_DATA_SIZE/PAGE_SIZE)
#endif

#ifdef M24M01
#define PAGE_SIZE 						256
#define EEPROM_DATA_SIZE 				1024
#define PAGE_NUMBER 					(EEPROM_DATA_SIZE/PAGE_SIZE)
#endif

/*****************************************************************************/

uint8_t bytes_temp[4];

uint16_t bytes(uint16_t size,uint16_t offset)
{
	if((size+offset)<PAGE_SIZE)
		return size;
	else
		return PAGE_SIZE;

}

void EEPROM_Write(uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	int pAddr= log2(PAGE_SIZE);

	uint16_t Starting_page =  page;
	uint16_t Ending_page = page + ((size+offset)/PAGE_SIZE);

	uint16_t number_of_pages =(Ending_page - Starting_page)+1;
	uint16_t position = 0;

	for(int i=0; i<number_of_pages;i++)
	{
		uint16_t MemAddr = Starting_page<< pAddr | offset;
		uint16_t remainingbytes = bytes(size,offset);

		HAL_I2C_Mem_Write(EEPROM_I2C, EEPROM_ADDR, MemAddr, 2, (uint8_t*)(&data[position]), remainingbytes, 1000);
		//HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout)
		Starting_page += 1;
		offset=0;
		size = size - remainingbytes;
		position += remainingbytes;

		HAL_Delay(5);
	}

}

void EEPROM_Read(uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	int pAddr = log2(PAGESIZE);

	uint16_t Starting_page =  page;
	uint16_t Ending_page = page + ((size+offset)/PAGE_SIZE);

	uint16_t number_of_pages =(Ending_page- Starting_page)+1;
	uint16_t position = 0;


	for (int i=0; i<number_of_pages;i++)
	{
		uint16_t MemAddr = Starting_page << pAddr | offset;
		uint16_t remainingbytes = bytes(size,offset);

		HAL_I2C_Mem_Read(EEPROM_I2C, EEPROM_ADDR, MemAddr, 2, &data[position], remainingbytes, 100);

		Starting_page += 1;
		offset=0;
		size = size - remainingbytes;
		position += remainingbytes;
	}
}

/*
 *
 *
 *
 *
 * */

void EEPROM_Page_Erease(uint16_t page){

	int pAddr = log2(PAGE_SIZE);

	uint16_t Starting_page =  page;
	uint16_t MemAddr = Starting_page<< pAddr;

	uint8_t data[PAGE_SIZE];
	memset(data,0xFF,PAGE_SIZE);

	HAL_I2C_Mem_Write(EEPROM_I2C, EEPROM_ADDR, MemAddr, 2, (uint8_t*)(&data), PAGE_SIZE, 100);

	HAL_Delay(5);

}


