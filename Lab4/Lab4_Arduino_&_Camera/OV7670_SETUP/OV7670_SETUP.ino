/*
 * @date: 10.25.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Lab 4
 */

//NOTE - all values will be read in hexadecimal format. All addresses & write values should also be written in hex

#include <Wire.h>
#define OV7670_I2C_ADDRESS = 0x15; //7 MSB from address = 0b0010101 in binary, 21 in decimal, 0x15 in hex
/*
 * 42 for write --> 0b00101010
 * 43 for read  --> 0b00101011

 * The address you give the Arduino I2C library should NOT include the LSB 
 * That is, the read/write addresses you get from datasheet are 7 bit I2C addresses + 1 or a 0 depending on if it's a read or write address
 * Just give the Arduino library the upper seven bits
 */

//---------------------------------------------------//
//                    MAIN PROGRAM                   //
//---------------------------------------------------//
void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  // TODO: READ KEY REGISTERS
  read_key_registers();
  
  delay(100);
  // TODO: WRITE KEY REGISTERS

  set_color_matrix();
}

void loop(){
}

//---------------------------------------------------//
//              FUNCTION DEFINITIONS                 //
//---------------------------------------------------//
void read_key_registers(){
  /*TODO: DEFINE THIS FUNCTION*/
  // You can also add something more intelligent to the routine called read_key_registers such that it automatically outputs what you have written
}

byte read_register_value(int register_address){
  byte data = 0;
  Wire.beginTransmission(OV7670_I2C_ADDRESS);
  Wire.write(register_address);
  Wire.endTransmission();
  Wire.requestFrom(OV7670_I2C_ADDRESS,1);
  while(Wire.available()<1);
  data = Wire.read();
  return data;
}

String OV7670_write(int start, const byte *pData, int size){
    int n,error;
    Wire.beginTransmission(OV7670_I2C_ADDRESS);
    n = Wire.write(start);
    if(n != 1){
      return "I2C ERROR WRITING START ADDRESS";   
    }
    n = Wire.write(pData, size);
    if(n != size){
      return "I2C ERROR WRITING DATA";
    }
    error = Wire.endTransmission(true);
    if(error != 0){
      return String(error);
    }
    return "no errors :)";
}
String OV7670_write_register(int reg_address, byte data){
  return OV7670_write(reg_address, &data, 1);
}
void set_color_matrix(){
    OV7670_write_register(0x4f, 0x80);
    OV7670_write_register(0x50, 0x80);
    OV7670_write_register(0x51, 0x00);
    OV7670_write_register(0x52, 0x22);
    OV7670_write_register(0x53, 0x5e);
    OV7670_write_register(0x54, 0x80);
    OV7670_write_register(0x56, 0x40);
    OV7670_write_register(0x58, 0x9e);
    OV7670_write_register(0x59, 0x88);
    OV7670_write_register(0x5a, 0x88);
    OV7670_write_register(0x5b, 0x44);
    OV7670_write_register(0x5c, 0x67);
    OV7670_write_register(0x5d, 0x49);
    OV7670_write_register(0x5e, 0x0e);
    OV7670_write_register(0x69, 0x00);
    OV7670_write_register(0x6a, 0x40);
    OV7670_write_register(0x6b, 0x0a);
    OV7670_write_register(0x6c, 0x0a);
    OV7670_write_register(0x6d, 0x55);
    OV7670_write_register(0x6e, 0x11);
    OV7670_write_register(0x6f, 0x9f);
    OV7670_write_register(0xb0, 0x84);
}
