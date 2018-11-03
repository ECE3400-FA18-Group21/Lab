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

void setup_camera() {
  Wire.begin();

//--------------------------------------------------------------------------------//
//                          RESET ALL REGISTERS                                   //
//--------------------------------------------------------------------------------// 
//This is used because during testing, we set the registers multiple times 
  OV7670_write_register(0x12, 0b10000000);
  delay(100);
  
  Serial.println("------------------------------------------------------------------");
  Serial.println("          INITIAL VALUES BEFORE WRITING TO REGISTERS              ");
  Serial.println("------------------------------------------------------------------");                             
  read_key_registers();

//--------------------------------------------------------------------------------//
//                     STORE INITIAL REGISTER VALUES                              //
//--------------------------------------------------------------------------------//
  byte COM7 = read_register_value(0x12);                  //SCCB Register Reset, QCIF, Color Bar Enable
  byte COM3 = read_register_value(0x0C);                  //Enable scaling
  byte COM9 = read_register_value(0x14);                  //Automatic Gain Ceiling
  byte COM15 = read_register_value(0x40);                 //RGB565
  byte COM17 = read_register_value(0x42);                 //DSP color bar enable
  byte CLKRC = read_register_value(0x11);                 //Use external clock as internal clock
  byte MVFP = read_register_value(0x1E);                  //Mirror & VFlip enable

//--------------------------------------------------------------------------------//
//                   ASSIGN MODIFIED VALUES TO VARIABLES                          //
//--------------------------------------------------------------------------------//
  byte RESET          =       0b10000000;
  COM7               |=       0b00001110;
  COM3               |=       0b00001000;
  COM9                =       0b00000001;
  COM15              |=       0b11010000;
  COM17              |=       0b00001000;
  CLKRC              |=       0b11000000;
  MVFP               |=       0b00110000;

//--------------------------------------------------------------------------------//
//                                WRITE TO REGISTERS                              //
//--------------------------------------------------------------------------------//
  OV7670_write_register(0x12, RESET);
  delay(100);
  OV7670_write_register(0x12, COM7);
  OV7670_write_register(0x0C, COM3); 
  OV7670_write_register(0x14, COM9);                      
  OV7670_write_register(0x40, COM15);                
  OV7670_write_register(0x42, COM17);
  OV7670_write_register(0x11, CLKRC);
  OV7670_write_register(0x1E, MVFP);

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
  Serial.print(read_register_value(0x12), BIN);
  Serial.println("");
  Serial.print("COM7 (QCIF & color bar enable) = ");
  Serial.print(read_register_value(0x12), BIN);
  Serial.println("");
  Serial.print("COM3 (Enable scaling) = ");
  Serial.print(read_register_value(0x0C), BIN);
  Serial.println("");
  Serial.print("COM9 (Automatic Gain Ceiling) = ");
  Serial.print(read_register_value(0x14), BIN);
  Serial.println("");
  Serial.print("COM15 (RGB565) = ");
  Serial.print(read_register_value(0x40), BIN);
  Serial.println("");
  Serial.print("COM17 (DSP color bar enable) = ");
  Serial.print(read_register_value(0x42), BIN);
  Serial.println("");
  Serial.print("CLKRC (Use external clock as internal clock) = ");
  Serial.print(read_register_value(0x11), BIN);
  Serial.println("");
  Serial.print("MVFP (Mirror & VFlip enable) = ");
  Serial.print(read_register_value(0x1E), BIN);
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
