/*
 * eeprom.c
 *
 *  Created on: Feb 4, 2022
 *      Author: Mucahit & Baykal
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


/******************************Define the model of EEPROM***************************************/

//#define M24M01
//#define M24512
#define M24256


/****************************** Property definition of EEPROM *******************************/

#ifdef M24512
#define EEPROM_PAGE_SIZE 				128
#define EEPROM_DATA_SIZE 				512*1024
#define PAGE_NUMBER 					(EEPROM_DATA_SIZE/EEPROM_PAGE_SIZE)
#endif


#ifdef M24256
#define EEPROM_PAGE_SIZE 				64
#define EEPROM_DATA_SIZE 				256*1024
#define PAGE_NUMBER 					(EEPROM_DATA_SIZE/EEPROM_PAGE_SIZE)
#endif

#ifdef M24M01
#define EEPROM_PAGE_SIZE 				256
#define EEPROM_DATA_SIZE 				1024*1024
#define PAGE_NUMBER 					(EEPROM_DATA_SIZE/EEPROM_PAGE_SIZE)
#endif


/*********************************************************************
  * @fn 			-	Calculation_Remaining_Bytes
  *
  * @brief			-	Calculation of remaining bytes
  * @brief			-	This function is used to find the remaining bytes
  * 				-   in order to detect if the (size + offset) exceeds EEPROM_PAGE_SIZE
  *
  * @param			-	offset 	(offset of the given page)
  * @param			-	size	(size of the data)
  *
  * @return			-	size
  *
  *@Note			-	None
  *
  */
uint16_t Calculation_Remaining_Bytes(uint16_t size,uint16_t offset)
{


	if((size+offset)<EEPROM_PAGE_SIZE)

		return size;

	else

		return EEPROM_PAGE_SIZE-offset;
}

/*********************************************************************
  * @fn 			-	EEPROM_Write
  *
  * @brief			-	EEPROM Write Function
  * @brief			-	This function is used to write at specific page/pages from the given starting memory address
  *
  * @param			-	page 	(page number. Range from 0 to PAGE_NUMBER-1)
  * @param			-	offset 	(offset of the given page. Range from 0 to EEPROM_PAGE_SIZE-1 )
  * @param			-	data	(data buffer)
  * @param			-	size	(size of the data)
  *
  * @return			-	None
  *
  *@Note			-	None
  *
  */
void EEPROM_Write(uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	int pAddr= log2(EEPROM_PAGE_SIZE);
	//int pAddr = log(EEPROM_PAGE_SIZE)/log(2)

	uint16_t Starting_page =  page;
	uint16_t Ending_page = page + ((size+offset)/EEPROM_PAGE_SIZE);

	uint16_t number_of_pages =(Ending_page - Starting_page)+1;
	uint16_t position = 0;


	for(int i=0; i<number_of_pages;i++)
	{
		uint16_t MemAddr = Starting_page<< pAddr | offset;
		uint16_t remainingbytes = Calculation_Remaining_Bytes(size,offset);

		HAL_I2C_Mem_Write(EEPROM_I2C, EEPROM_ADDR, MemAddr, 2, &data[position], remainingbytes, 1000);
		Starting_page += 1;
		offset=0;
		size = size - remainingbytes;
		position += remainingbytes;

		HAL_Delay(5);
	}

}

/*********************************************************************
  * @fn 			-	EEPROM_Read
  *
  * @brief			-	EEPROM Read Function
  * @brief			-	This function is used to read specific page/pages from the given memory address
  *
  * @param			-	page 	(Page number. Range from 0 to PAGE_NUMBER-1)
  * @param			-	offset 	(Offset of the given page. Range from 0 to EEPROM_PAGE_SIZE-1 )
  * @param			-	data	(data buffer)
  * @param			-	size	(size of the data)
  *
  * @return			-	None
  *
  *@Note			-	None
  *
  */
void EEPROM_Read(uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
{
	int pAddr = log2(EEPROM_PAGE_SIZE);

	uint16_t Starting_page =  page;
	uint16_t Ending_page = page + ((size+offset)/EEPROM_PAGE_SIZE);

	uint16_t number_of_pages =(Ending_page- Starting_page)+1;
	uint16_t position = 0;


	for (int i=0; i<number_of_pages;i++)
	{
		uint16_t MemAddr = Starting_page << pAddr | offset;
		uint16_t remainingbytes = Calculation_Remaining_Bytes(size,offset);

		HAL_I2C_Mem_Read(EEPROM_I2C, EEPROM_ADDR, MemAddr, 2, &data[position], remainingbytes, 100);

		Starting_page += 1;
		offset=0;
		size = size - remainingbytes;
		position += remainingbytes;
	}
}

/*********************************************************************
  * @fn 			-	EEPROM_Page_Erase
  *
  * @brief			-	EEPROM Page Erase Function
  * @brief			-	This function is used to erase a specific page with writing 0xFF
  * @brief			-	at the corresponding page.
  *
  * @param			-	page 	(Page number. Range from 0 to PAGE_NUMBER-1)
  *
  * @return			-	None
  *
  *@Note			-	None
  *
  */
void EEPROM_Page_Erease(uint16_t page)
{

	int pAddr = log2(EEPROM_PAGE_SIZE);

	uint16_t Starting_page =  page;
	uint16_t MemAddr = Starting_page<< pAddr;

	uint8_t data[EEPROM_PAGE_SIZE];

	memset(data,0xFF,EEPROM_PAGE_SIZE);

	HAL_I2C_Mem_Write(EEPROM_I2C, EEPROM_ADDR, MemAddr, 2, (uint8_t*)(&data), EEPROM_PAGE_SIZE, 100);

	HAL_Delay(5);

}


