## Electrically Erasable Programmable Read-Only Memory (EEPROM)
EEPROM, or Electrically Erasable Programmable Read-Only Memory, is a type of device that allows you to store small chunks of data and retrieve it later even if the device has been power cycled. A lot of modern microcontrollers – such as the ATmega328 – contain some built-in EEPROM, but that doesn't mean that you can't add more! Serial EEPROM devices like the Microchip 24-series EEPROM allow you to add more memory to any device that can speak I²C. Today we're going to learn how to read and write serial EEPROM devices 

EEPROM Driver Development
Electrically Erasable Programmable Read-Only Memory is a non-volatile memory usually integrated in MCUs. It is mainly used to store volatile variables and configuration data. Moreover, EEPROM also has a unique lockable ID feature so that any critical code can be stored at the reserved sector in it. The connection of the EEPROM and Pull-up resistors shown in Figure 1.

 ![image](https://user-images.githubusercontent.com/43001724/172898430-61807f83-4e80-49b2-8fb5-3b95f5129788.png)
Figure 1 EEPROM connection with a microcontroller over I2C lines

We are assigned to select a-64 Kbytes EEPROM chip, then, developing read, write, erase functions based on I2C hardware protocol. The reason of selecting I2C protocol is speed and price concerns.
In Figure 1, R1 and R2 resistors are, called pull-up resistors, connected data and clock lines. The resistors are also connected to +3.3V voltage source. A pull-up resistor is used to ensure keeping signal at a known. For instance, in the above figure clock and data lines are kept as high (3.3V) to ensure communication. 

## Reading and Writing
Most of the time when you're using an EEPROM in conjunction with a microcontroller you won't actually need to see all of the contents of the memory at once. You'll just read and write bytes here and there as needed.
