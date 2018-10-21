/*
   @date: 09.28.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Benchmark Sensors
*/
#include "maze.h"

/* Helper function for getting the Nth bit of a byte*/
byte getNthBit(byte n, byte data) {
  return (data >> n) & 0x01;
}

Maze::Maze() {
  for (byte i = 0; i < 18; i++)
    walls[i] = 0; //Robot starts knowing none of the walls
  pos = 0;     //Robot starts at 0,0
  heading = 2; //Robot starts facing downward
  for (byte i = 0; i < 9; i++)
    visited[i] = 0;
}

/*
   turnLeft() tells the Maze object that the robot is turning left, and to adjust the
   representation accordingly.
*/
void Maze::turnLeft() {
  int temp_heading = (int)heading;
  temp_heading = (temp_heading - 1) % 4;
  heading = (0xFF) & temp_heading; //convert to byte
}
/*
   turnRight() tells the Maze object that the robot is turning right, and to adjust the
   representation accordingly.
*/
void Maze::turnRight() {
  int temp_heading = (int)heading;
  temp_heading = (temp_heading + 1) % 4;
  heading = (0xFF) & temp_heading;
}
/*
   advanceIntersection(frontWall, leftWall, rightWall) tells the Maze object that the robot
   has moved one square forward and sees the following walls adjacent to the square
*/
void Maze::advanceIntersection(bool frontWall, bool leftWall, bool rightWall) {
  int temp_heading = (int)heading;
  // take all wall boolean values to be in a standard heading, that is front --> 0,
  // left --> 3, right --> 1. Then rotate these locations by the heading
  // (achieved by addition) mod 4
  int front = (0 + temp_heading) % 4;
  int left = (3 + temp_heading) % 4;
  int right = (1 + temp_heading) % 4;
  // convert data to a bit mask, that is bits 0-3 are 1 if there is a wall at that position
  // for the current interesection
  byte mask = (frontWall << front) | (leftWall << left) | (rightWall << right);
  // retrieve position of robot
  int x = (int)(pos >> 4);
  int y = (int)(pos & 0x0F);
  // OR the values in the bitmask with the corresponding wall positions
  walls[y]      |= (0x01) && mask;
  walls[y + 1]  |= (0x02) && mask;
  walls[x + 9]  |= (0x04) && mask;
  walls[x + 10] |= (0x08) && mask;
}

byte Maze::getX() {
  return (pos >> 4);
}

byte Maze::getY() {
  return (pos & 0x0F);
}

String Maze::getGUIMessage(byte x, byte y) {
  //x, y are raster positions
  bool north_bool;
  bool south_bool;

  if (y == 0) {
    if (x == 0) {
      north_bool = 1;
      west_bool = 1;
      south_bool = walls[x+9] & (0x1 << y);
      east_bool = walls[y] & (0x1 << x);
    }
    else if (x == 8) {
      north_bool = 1;
      south_bool = walls[x+9] & (0x1 << y);
      west_bool = walls[y] & (0x1 << (x-1));
      east_bool = 1;    
    }
    else {
      north_bool = 1;
      south_bool = walls[x+9] & (0x1 << y);
      west_bool = walls[y] & (0x1 << (x-1));
      east_bool = walls[y] & (0x1 << x);
    }
  }
  else if (y == 8) {
    if (x == 0) {
      north_bool = walls[x+9] & (0x1 << (y-1));
      south_bool = 1;
      west_bool = 1
      east_bool = walls[y] & (0x1 << x);
    }
    else if (x == 8) {
      north_bool = walls[x+9] & (0x1 << (y-1));
      south_bool = 1;
      west_bool = walls[y] & (0x1 << (x-1));
      east_bool = 1;
    }
    else {
      north_bool = walls[x+9] & (0x1 << (y-1));
      south_bool = walls[x+9] & (0x1 << y);
      west_bool = walls[y] & (0x1 << (x-1));
      south_bool = 1;
    }
  }
  else {
      north_bool = walls[x+9] & (0x1 << (y-1));
      south_bool = walls[x+9] & (0x1 << y);
      west_bool = walls[y] & (0x1 << (x-1));
      east_bool = walls[y] & (0x1 << x);
  }
  
  String north = north_bool ? "true" : "false";
  String south = south_bool ? "true" : "false";
  String west = west_bool ? "true" : "false";
  String east = east_bool ? "true" : "false";
  char buffer[65];
  int n;
  n = sprintf(buffer, "%d,%d,north=%s,south=%s,west=%s,east=%s", y, x, north, south, west, east); //x y flipped b/c GUI takes row # first
  for (int i = 0; i < n; i++) {
    Serial.print(buffer[i]);
  }
  Serial.println();
  
}

void Maze::printInfo() {
  /* Print Upper Bounding Wall of grid */
  String to_print = " _ _ _ _ _ _ _ _ _ ";
  Serial.println(to_print);

  /* Print middle of Grid*/
  for (byte y = 0; y < 8; y++) {
    to_print = "|";
    for (byte x = 0; x < 16; x++) {
      if ((x % 2) & getNthBit((x / 2), walls[y]) ) { // x is odd- check walls[0-8] for vertical walls
        to_print = String(to_print + "|");
      }
      else if (getNthBit(y, walls[(9 + (x % 2))])) { // x is even- check walls[9-17] for horizontal walls
        to_print = String(to_print + "_");
      }
      else {
        to_print = String(to_print + " ");
      }
    }
    to_print = String(to_print + "|");
    Serial.println(to_print);
  }

  /* Print lower bounding wall of grid */
  to_print = "|";
  for (byte x = 0; x < 16; x++) {
    if ((x % 2) & getNthBit((x / 2), walls[8]) ) { // x is odd- check walls[0-8] for vertical walls
      to_print = String(to_print + "|");
    }
    else if (!(x % 2)) { // x is even- put down a horizontal wall
      to_print = String(to_print + "_");
    }
    else {
      to_print = String(to_print + " ");
    }
  }
  to_print = String(to_print + "|");
  Serial.println(to_print);



  //Serial.println(" _ _ _ _ _ _ _ _ _ ");
  //Serial.println(" _ _ _ _ _ _ _ _ _ ");
  //Serial.println("|_|_|_|_|_|_|_|_|_|");
  //Serial.println("|_|_|_|_|_|_|_|_|_|");

}
