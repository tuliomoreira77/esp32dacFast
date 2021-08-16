# esp32dacFast
Library writen by Tulio_Moreira, feel free to modify and share as you want. 

This library allows to use esp32 dac in a faster way then the traditional function "dacWrite" (in free run this library can reach ~850khz write frequency, the tradional one can reach only ~200Khz).

Functions:
 - dacAttachPin(PIN_NUMBER) ---- set a output analog (can be pin 25 or 26);
 - dacFastWrite25(VALUE) ---- Write a value to output 25 (0 to 255);
 - dacFastWrite26(VALUE) ---- Write a value to outupt 26 (0 to 255);
