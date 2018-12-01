/*
   @date: 11.30.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Base Station - Milestone 4    --> *******FINAL VERSION*********
*/
#include "nordic_rf.h"
#include "maze.h"
#include <printf.h>
#include <RF24.h>

RF24 radio(7, 8);

Maze maze = Maze();

void setup() {
  Serial.begin(9600);
  printf_begin();
  RF24_rx_setup(radio);
  radio.printDetails();
}

void loop() {
  //---------------------------------------------------//
  //                RADIO COMMUNICATION                //
  //---------------------------------------------------//
  byte received = 0;
  received = RF24_rx_read(radio);

  //---------------------------------------------------//
  //         PARSE INSTRUCTIONS & UPDATE MAZE          //
  //---------------------------------------------------//
  int instructions[8];
  splitByte(received, instructions);
  //Command Type = 00
  if(instructions[1]==0 && instructions[0]==0){
    maze.turnLeft();
    //Serial.println("Turn Left = 00");
  }
  //Command Type = 01
  else if(instructions[1]==0 && instructions[0]==1){
    maze.turnRight();
    //Serial.println("Turn Right = 01");
  } 
  //Command Type = 10
  else if(instructions[1]==1 && instructions[0]==0){
      bool frontWall = convert_Int_to_Bool(instructions[2]);
      bool leftWall = convert_Int_to_Bool(instructions[3]);
      bool rightWall = convert_Int_to_Bool(instructions[4]);
      maze.advanceIntersection(frontWall, leftWall, rightWall);
      //Serial.println("Advance Intersection = 10");
  }
  else
    Serial.println("Invalid command");
  
  //---------------------------------------------------//
  //                     UPDATE GUI                    //
  //---------------------------------------------------//
  bool treasure0 = convert_Int_to_Bool(instructions[5]); //LSB
  bool treasure1 = convert_Int_to_Bool(instructions[6]);
  bool treasure2 = convert_Int_to_Bool(instructions[7]); //MSB
  maze.getGUIMessage(maze.getX(), maze.getY(), treasure2, treasure1, treasure0);  
  delay(100);
}

//Breaks a byte into an 8-element int array by bit
void splitByte(byte b, int variable[8]){
  byte i;
  for (i=0; i < 8; ++i )
  {
    variable[i] = b & 1;
    b = b >> 1;
  }
}
//Converts int --> bool 
bool convert_Int_to_Bool(int i){
  if(i)
    return true;
  else
    return false;
}
