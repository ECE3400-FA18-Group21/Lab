/*
   @date: 11.01.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Lab 4
*/

//NOTE - all values will be read in hexadecimal format. All addresses & write values should also be written in hex

#include <Wire.h>
#define OV7670_I2C_ADDRESS 0x21
/*
   0x42 for write
   0x43 for read

   The address you give the Arduino I2C library should NOT include the LSB
   That is, the read/write addresses you get from datasheet are 7 bit I2C addresses + 1 or a 0 depending on if it's a read or write address
   Just give the Arduino library the upper seven bits
*/

int FPGA_communication_pin = 5;

//---------------------------------------------------//
//                    MAIN PROGRAM                   //
//---------------------------------------------------//
void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(FPGA_communication_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // TODO: READ KEY REGISTERS
  Serial.println("------------------------------------------------------------------");
  Serial.println("          INITIAL VALUES BEFORE WRITING TO REGISTERS              ");
  Serial.println("------------------------------------------------------------------");
  OV7670_write_register(0x12, 0b10000000);                             //reset all registers
  read_key_registers();
  byte reset = read_register_value(0x12);
  byte res_scale_en = read_register_value(0x0C);
  byte ext_CLK = read_register_value(0x11);
  byte qcif = read_register_value(0x12);
  byte rgb565 = read_register_value(0x40);
  byte color_bar_en = read_register_value(0x12);
  byte dsp_color_bar_en = read_register_value(0x42);
  byte mirror_image = read_register_value(0x1E);
  byte vert_flip_image = read_register_value(0x1E);
  //byte auto_gain_ceil = read_register_value(0x00);
  delay(100);

  //Assign modified values to variables to be written to registers
  reset            |= 0b10000000;
  res_scale_en     |= 0b00001000;
  ext_CLK          |= 0b01000000;
  qcif             |= 0b00001100;
  rgb565           |= 0b00001000;
  color_bar_en     |= 0b00000010;
  dsp_color_bar_en |= 0b00001000;
  mirror_image     |= 0b00100000;
  vert_flip_image  |= 0b00010000;
  //auto_gain_ceil   |= 0x00110000;

  // TODO: WRITE KEY REGISTERS
  OV7670_write_register(0x12, reset);                             //reset all registers
  delay(100);
  OV7670_write_register(0x0C, res_scale_en);                      //enable manual resolution scaling
  OV7670_write_register(0x11, ext_CLK);                           //use external clock as internal clock
  OV7670_write_register(0x12, (qcif | color_bar_en));
  OV7670_write_register(0x40, rgb565);
  OV7670_write_register(0x42, dsp_color_bar_en);
  OV7670_write_register(0x1E, (mirror_image | vert_flip_image));
  //OV7670_write_register(0x14, auto_gain_ceil);

  set_color_matrix();

  // TODO: READ KEY REGISTERS
  Serial.println("");
  Serial.println("------------------------------------------------------------------");
  Serial.println("                 AFTER WRITING TO REGISTERS                       ");
  Serial.println("------------------------------------------------------------------");
  read_key_registers();
  delay(100);
  Serial.println("------------------------------------------------------------------");
  Serial.println("                           NOTES                                  ");
  Serial.println("------------------------------------------------------------------");
  Serial.println("Reset, Color Bar Enable, and DSP Color Bar Enable are the SAME registers");
  Serial.println("Mirror Image and Vertically Flip Image are the SAME registers");
}
void loop(){
}

void loops1() {
  int value = digitalRead(FPGA_communication_pin);
  if (value) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("------------------------------------------------------------------");
    Serial.println("                           RED DETECTED                           ");
    Serial.println("------------------------------------------------------------------");
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("------------------------------------------------------------------");
    Serial.println("                          BLUE DETECTED                           ");
    Serial.println("------------------------------------------------------------------");
  }
}

void loops() {
  //---------------------------------------------------//
  //               SERIAL COMMUNICATION                //
  //---------------------------------------------------//
  byte received = 0;
  if(Serial.available()) {
    received = Serial.read();
  }

  //---------------------------------------------------//
  //         PARSE INSTRUCTIONS & UPDATE MAZE          //
  //---------------------------------------------------//
  int instructions[8];
  splitByte(received, instructions);

  //Command Type = 0000   --> no treasure
  if (instructions[0]==0) {
    Serial.println("No treasure detected");
  }
  //Command Type = 0001   --> Red-Triangle
  else if (instructions[3]==0 && instructions[2]==0 && instructions[1]==0 && instructions[0]==1) {
    Serial.println("Red Triangle Treasure detected");
  }
  //Command Type = 0011   --> Blue-Triangle
  else if (instructions[3]==0 && instructions[2]==0 && instructions[1]==1 && instructions[0]==1) {
    Serial.println("Blue Triangle Treasure detected");
  }
  //Command Type = 0101   --> Red-Square
  else if (instructions[3]==0 && instructions[2]==1 && instructions[1]==0 && instructions[0]==1) {
    Serial.println("Red Square Treasure detected");
  }
  //Command Type = 0111   --> Blue-Square
  else if (instructions[3]==0 && instructions[2]==1 && instructions[1]==1 && instructions[0]==1) {
    Serial.println("Blue Square Treasure detected");
  }
  //Command Type = 1001   --> Red-Circle
  else if (instructions[3]==1 && instructions[2]==0 && instructions[1]==0 && instructions[0]==1) {
    Serial.println("Red Circle Treasure detected");
  }
  //Command Type = 1011   --> Blue-Circle
  else if (instructions[3]==1 && instructions[2]==0 && instructions[1]==1 && instructions[0]==1) {
    Serial.println("Blue Circle Treasure detected");
  }
  else
    Serial.println("Invalid command");
}

//---------------------------------------------------//
//              FUNCTION DEFINITIONS                 //
//---------------------------------------------------//
void read_key_registers() {
  /*TODO: DEFINE THIS FUNCTION*/
  Serial.print("Reset register = ");
  Serial.print(read_register_value(0x12), BIN);
  Serial.println("");
  Serial.print("Enable manual resolution scaling = ");
  Serial.print(read_register_value(0x0C), BIN);
  Serial.println("");
  Serial.print("Use external clock as internal clock = ");
  Serial.print(read_register_value(0x11), BIN);
  Serial.println("");
  Serial.print("QCIF = ");
  Serial.print(read_register_value(0x12), BIN);
  Serial.println("");
  Serial.print("RGB565 = ");
  Serial.print(read_register_value(0x40), BIN);
  Serial.println("");
  Serial.print("Color bar enable = ");
  Serial.print(read_register_value(0x12), BIN);
  Serial.println("");
  Serial.print("DSP color bar enable = ");
  Serial.print(read_register_value(0x42), BIN);
  Serial.println("");
  Serial.print("Mirror image = ");
  Serial.print(read_register_value(0x1E), BIN);
  Serial.println("");
  Serial.print("Vertically flip image = ");
  Serial.print(read_register_value(0x1E), BIN);
  Serial.println("");
  //Serial.print("Automatic gain ceiling = ");
  //Serial.print(read_register_value(0x14), BIN);
  //Serial.println("");
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
//Breaks a byte into an 8-element int array by bit
void splitByte(byte b, int variable[8]) {
  byte i;

  for (i = 0; i < 8; ++i )
  {
    variable[i] = b & 1;
    b = b >> 1;
  }
}
