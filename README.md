## Electrically Erasable Programmable Read-Only Memory (EEPROM)
EEPROM, or Electrically Erasable Programmable Read-Only Memory, is a type of device that allows you to store small chunks of data and retrieve it later even if the device has been power cycled. 

Many applications require storing small quantities of system related data (calibration values, device configuration) in a non-volatile memory, so that it can be used or modified and reused even after power cycling the system. EEPROMs are primarily used for this purpose. EEPROMs have the ability to erase and write individual bytes of memory many times over and the programmed locations retain the data over a long period even when the system is powered down.

## Reading and Writing
Most of the time when you're using an EEPROM in conjunction with a microcontroller you won't actually need to see all of the contents of the memory at once. You'll just read and write bytes here and there as needed.
