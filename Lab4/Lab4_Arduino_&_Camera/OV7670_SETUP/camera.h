/*
   @date: 11.02.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Lab 4 - Arduino & Camera Team 
*/
#include <Arduino.h>


/**
 * Performs camera setup by writing to required registers
 */
void setup_camera();

/**
 * Used as diagnostic tool
 * Serial prints the value in all required registers
 */
void read_key_registers();

/**
 * Function to read a specific register
 */
byte read_register_value(int register_address);

/**
 * 
 */
String OV7670_write(int start, const byte *pData, int size);

/**
 * 
 */
String OV7670_write_register(int reg_address, byte data);

/**
 * 
 */
void set_color_matrix();
