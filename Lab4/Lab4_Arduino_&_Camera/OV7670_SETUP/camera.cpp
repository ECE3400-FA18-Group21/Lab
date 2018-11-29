/*
   @date: 11.02.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Lab 4 - Arduino & Camera Team 
*/
#define OV7670_I2C_ADDRESS 0x21
#include <Wire.h>
#include "camera.h"
/*
   • Slave write address = 0x42
   • Slave read address  = 0x43
   • The address you give the Arduino I2C library should NOT include the LSB
*/

void setup_camera(bool testMode) {
  Wire.begin();

  //--------------------------------------------------------------------------------//
  //                          RESET ALL REGISTERS                                   //
  //--------------------------------------------------------------------------------// 
  //This is used because during testing, we set the registers multiple times
  if(testMode){ 
    OV7670_write_register(0x12, 0b10000000);
  }
  delay(100);
  
  Serial.println("------------------------------------------------------------------");
  Serial.println("          INITIAL VALUES BEFORE WRITING TO REGISTERS              ");
  Serial.println("------------------------------------------------------------------");                             
  read_key_registers();

  //--------------------------------------------------------------------------------//
  //                                WRITE TO REGISTERS                              //
  //--------------------------------------------------------------------------------//
  OV7670_write_register(0x12, 0x80);   //COM7,    SCCB Register Reset
  delay(100);
  if(testMode)
    OV7670_write_register(0x12, 0x0e); //COM7,    QCIF, RGB output, Color bar enable
  else{
    OV7670_write_register(0x12, 0x0c); //COM7,    QCIF, RGB output, Color bar disable
  }
  OV7670_write_register(0x0c, 0x08);   //COM3,    Enable scaling
  //OV7670_write_register(0x14, 0x01);   //COM9,    Automatic gain ceiling, freeze AGC/AEC
  OV7670_write_register(0x40, 0xd0);   //COM15,   RGB 565 Output
  if(testMode) {
    OV7670_write_register(0x42, 0x08); //COM17,   DSP color bar enable
  }
  else {
    OV7670_write_register(0x42, 0x00); //COM17,   DSP color bar disable
  }
  OV7670_write_register(0x11, 0xc0);   //CLKRC,   Use internal clock as external clock
  OV7670_write_register(0x1e, 0x30);   //MVFP,    Mirror & VFlip enable

  set_color_matrix();

  Serial.println("");
  Serial.println("------------------------------------------------------------------");
  Serial.println("                 AFTER WRITING TO REGISTERS                       ");
  Serial.println("------------------------------------------------------------------");
  read_key_registers();
  Serial.println("------------------------------------------------------------------");
  Serial.println("                           NOTES                                  ");
  Serial.println("------------------------------------------------------------------");
  Serial.println("Reset, Color Bar Enable, and QCIF are the SAME register (COM7)");
  Serial.println("Mirror Image and Vertically Flip Image are the SAME register (MVFP)");
}
//--------------------------------------------------------------------------------//
//                             HELPER FUNCTIONS                                   //
//--------------------------------------------------------------------------------//
void read_key_registers() {
  Serial.print("COM7 (SCCB Register Reset) = ");
  Serial.print(read_register_value(0x12), HEX);
  Serial.println("");
  Serial.print("COM7 (QCIF, RGB output & Color bar enable) = ");
  Serial.print(read_register_value(0x12), HEX);
  Serial.println("");
  Serial.print("COM3 (Enable scaling) = ");
  Serial.print(read_register_value(0x0C), HEX);
  Serial.println("");
  Serial.print("COM9 (Automatic Gain Ceiling, freeze AGC/AEC) = ");
  Serial.print(read_register_value(0x14), HEX);
  Serial.println("");
  Serial.print("COM15 (RGB565) = ");
  Serial.print(read_register_value(0x40), HEX);
  Serial.println("");
  Serial.print("COM17 (DSP color bar enable) = ");
  Serial.print(read_register_value(0x42), HEX);
  Serial.println("");
  Serial.print("CLKRC (Use external clock as internal clock) = ");
  Serial.print(read_register_value(0x11), HEX);
  Serial.println("");
  Serial.print("MVFP (Mirror & VFlip enable) = ");
  Serial.print(read_register_value(0x1E), HEX);
  Serial.println("");
}
byte read_register_value(int register_address) {
  byte data = 0;
  Wire.beginTransmission(OV7670_I2C_ADDRESS);
  Wire.write(register_address);
  Wire.endTransmission();
  Wire.requestFrom(OV7670_I2C_ADDRESS, 1);
  while (Wire.available() < 1);
  data = Wire.read();
  return data;
}
String OV7670_write(int start, const byte *pData, int size) {
  int n, error;
  Wire.beginTransmission(OV7670_I2C_ADDRESS);
  n = Wire.write(start);
  if (n != 1) {
    return "I2C ERROR WRITING START ADDRESS";
  }
  n = Wire.write(pData, size);
  if (n != size) {
    return "I2C ERROR WRITING DATA";
  }
  error = Wire.endTransmission(true);
  if (error != 0) {
    return String(error);
  }
  return "no errors :)";
}
String OV7670_write_register(int reg_address, byte data) {
  return OV7670_write(reg_address, &data, 1);
}
void set_color_matrix() {
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
