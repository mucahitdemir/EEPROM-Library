## Electrically Erasable Programmable Read-Only Memory (EEPROM)
EEPROM, or Electrically Erasable Programmable Read-Only Memory, is a type of device that allows you to store small chunks of data and retrieve it later even if the device has been power cycled. A lot of modern microcontrollers – such as the ATmega328 – contain some built-in EEPROM, but that doesn't mean that you can't add more! Serial EEPROM devices like the Microchip 24-series EEPROM allow you to add more memory to any device that can speak I²C. Today we're going to learn how to read and write serial EEPROM devices 


## Reading and Writing
Most of the time when you're using an EEPROM in conjunction with a microcontroller you won't actually need to see all of the contents of the memory at once. You'll just read and write bytes here and there as needed.
