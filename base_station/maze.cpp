/*
   @date: 10.21.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Base Station Program - Lab3
*/
#include "maze.h"

/* Helper function for getting the Nth bit of a byte*/
byte getNthBit(byte n, byte data) {
  return (data >> n) & 0x01;
}

Maze::Maze() {
  for (byte i = 0; i < 18; i++)
    walls[i] = 0; //Robot starts knowing none of the walls
  for (byte i = 0; i < 9; i++)
    visited[i] = 0;
  pos = 0;     //Robot starts at 0,0
  heading = 2; //Robot starts facing downward
}

/*
   turnLeft() tells the Maze object that the robot is turning left, and to adjust the
   representation accordingly.
*/
void Maze::turnLeft() {
  byte temp_heading = heading;
  temp_heading = temp_heading - 1;
  temp_heading = temp_heading % 4;
  heading = temp_heading;
}
/*
   turnRight() tells the Maze object that the robot is turning right, and to adjust the
   representation accordingly.
*/
void Maze::turnRight() {
  byte temp_heading = heading;
  temp_heading = temp_heading + 1;
  temp_heading = temp_heading % 4;
  heading = temp_heading;
}
/*
   advanceIntersection(frontWall, leftWall, rightWall) tells the Maze object that the robot
   has moved one square forward and sees the following walls adjacent to the square
*/
void Maze::advanceIntersection(bool frontWall, bool leftWall, bool rightWall) {
  byte x_coord, y_coord, x_walls, y_walls, mask;

  // First update position
  switch (heading) {
    // North
    case 0:
      y_coord = getY();
      y_coord = y_coord - 1;
      pos = pos & 0xF0; // Clear y coordinate
      pos = pos | y_coord; // Set y coordinate
      break;
    //South
    case 2:
      y_coord = getY();
      y_coord = y_coord + 1;
      pos = pos & 0xF0; // Clear y coordinate
      pos = pos | y_coord; // Set y coordinate
      break;
    //East
    case 1:
      x_coord = getX();
      x_coord = x_coord + 1;
      pos = pos & 0x0F; // Clear x coordinate
      x_coord = x_coord << 4;
      pos = pos | x_coord; // Set x coordinate
      break;
    //West
    case 3:
      x_coord = getX();
      x_coord = x_coord - 1;
      pos = pos & 0x0F; // Clear x coordinate
      x_coord = x_coord << 4;
      pos = pos | x_coord; // Set x coordinate
      break;
    default:
      Serial.println("Heading error");
  }

  //Next Update walls[]
  //Get current coordinates
  x_coord = getX();
  y_coord = getY();

  y_walls = walls[y_coord];
  x_walls = walls[(x_coord + 9)];

  //Serial.println(y_coord);
  //walls[y_coord] = 0xFF;

  switch (heading) {
    // North
    case 0:
      if (frontWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (y_coord > 0)
          mask = 1 << (y_coord-1);
        else
          mask = 0;
        x_walls = x_walls | mask;
        walls[(x_coord + 9)] = x_walls;
      }
      if (leftWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (x_coord > 0)
          mask = 1 << (x_coord - 1);
        else
          mask = 0;
        y_walls = y_walls | mask;
        walls[y_coord] = y_walls;
      }
      if (rightWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (x_coord < 8)
          mask = 1 << x_coord;
        else
          mask = 0;
        y_walls = y_walls | mask;
        walls[y_coord] = y_walls;
      }
      break;
    //South
    case 2:
      if (frontWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (y_coord < 8)
          mask = 1 << y_coord;
        else
          mask = 0;
        x_walls = x_walls | mask;
        walls[(x_coord + 9)] = x_walls;
      }
      if (leftWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (x_coord < 8)
          mask = 1 << x_coord;
        else
          mask = 0;
        y_walls = y_walls | mask;
        walls[y_coord] = y_walls;
      }
      if (rightWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (x_coord > 0)
          mask = 1 << (x_coord - 1);
        else
          mask = 0;
        y_walls = y_walls | mask;
        walls[y_coord] = y_walls;
      }
      break;
    //East
    case 1:
      if (frontWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (x_coord < 8)
          mask = 1 << x_coord;
        else
          mask = 0;
        y_walls = y_walls | mask;
        walls[y_coord] = y_walls;
      }
      if (leftWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (y_coord > 0)
          mask = 1 << (y_coord - 1);
        else
          mask = 0;
        x_walls = x_walls | mask;
        walls[(x_coord + 9)] = x_walls;
      }
      if (rightWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (y_coord < 8)
          mask = 1 << y_coord;
        else
          mask = 0;
        x_walls = x_walls | mask;
        walls[(x_coord + 9)] = x_walls;
      }
      break;
    //West
    case 3:
      if (frontWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (x_coord > 0)
          mask = 1 << (x_coord - 1);
        else
          mask = 0;
        y_walls = y_walls | mask;
        walls[y_coord] = y_walls;
      }
      if (leftWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (y_coord < 8)
          mask = 1 << y_coord;
        else
          mask = 0;
        x_walls = x_walls | mask;
        walls[(x_coord + 9)] = x_walls;
      }
      if (rightWall) {
        // Make sure the wall is in bounds- otherwise don't change anything
        if (y_coord > 0)
          mask = 1 << (y_coord - 1);
        else
          mask = 0;
        x_walls = x_walls | mask;
        walls[(x_coord + 9)] = x_walls;
      }
      break;
    default:
      Serial.println("Heading error");
  }

}

byte Maze::getX() {
  return (pos >> 4);
}

byte Maze::getY() {
  return (pos & 0x0F);
}

void Maze::getGUIMessage(byte x, byte y) {
  bool north_bool;
  bool south_bool;
  bool west_bool;
  bool east_bool;

  if (y == 0) {
    if (x == 0) {
      north_bool = 1;
      west_bool = 1;
      south_bool = (walls[x+9] & (0x1 << y)) >> y;
      east_bool = (walls[y] & (0x1 << x)) >> x;
    }
    else if (x == 8) {
      north_bool = 1;
      south_bool = (walls[x+9] & (0x1 << y)) >> y;
      west_bool = (walls[y] & (0x1 << (x-1))) >> (x-1);
      east_bool = 1;    
    }
    else {
      north_bool = 1;
      south_bool = (walls[x+9] & (0x1 << y)) >> y;

      west_bool = (walls[y] & (0x1 << (x-1))) >> (x-1);
      east_bool = (walls[y] & (0x1 << x)) >> x;
    }
  }
  else if (y == 8) {
    if (x == 0) {
      north_bool = (walls[x+9] & (0x1 << (y-1))) >> (y-1);
      south_bool = 1;
      west_bool = 1;
      east_bool = (walls[y] & (0x1 << x)) >> x;
    }
    else if (x == 8) {
      north_bool = (walls[x+9] & (0x1 << (y-1))) >> (y-1);
      south_bool = 1;
      west_bool = (walls[y] & (0x1 << (x-1))) >> (x-1);
      east_bool = 1;
    }
    else {
      north_bool = (walls[x+9] & (0x1 << (y-1))) >> (y-1);
      south_bool = (walls[x+9] & (0x1 << y)) >> y;
      west_bool = (walls[y] & (0x1 << (x-1))) >> (x-1);
      south_bool = 1;
    }
  }
  else if (x == 0){
      north_bool = (walls[x+9] & (0x1 << (y-1))) >> (y-1);
      south_bool = (walls[x+9] & (0x1 << y)) >> y;
      west_bool = 1;
      east_bool = (walls[y] & (0x1 << x)) >> x;
  }
  else if (x == 8) {
      north_bool = (walls[x+9] & (0x1 << (y-1))) >> (y-1);
      south_bool = (walls[x+9] & (0x1 << y)) >> y;
      west_bool = (walls[y] & (0x1 << (x-1))) >> (x-1);
      east_bool = 1;
  }
  else {
      north_bool = (walls[x+9] & (0x1 << (y-1))) >> (y-1);
      south_bool = (walls[x+9] & (0x1 << y)) >> y;
      west_bool = (walls[y] & (0x1 << (x-1))) >> (x-1);
      east_bool = (walls[y] & (0x1 << x)) >> x;
  }
  char north_char[6];
  char south_char[6];
  char east_char[6];
  char west_char[6];
  String north = north_bool ? "true" : "false";
  String south = south_bool ? "true" : "false";
  String west = west_bool ? "true" : "false";
  String east = east_bool ? "true" : "false";
  north.toCharArray(north_char, 6);
  south.toCharArray(south_char, 6);
  west.toCharArray(west_char, 6);
  east.toCharArray(east_char, 6);
  char buffer[50];
  int n;
  n = sprintf(buffer, "%d,%d,north=%s,south=%s,west=%s,east=%s,robot=false", y, x, north_char, south_char, west_char, east_char); //x y flipped b/c GUI takes row # first
  for (int i = 0; i < n; i++) {
    Serial.print(buffer[i]);
  }
  Serial.println();
}

void Maze::printInfo() {
  Serial.println("Maze Info:");
  Serial.print("Current X Position: ");
  Serial.println(getX());
  Serial.print("Current Y Position: ");
  Serial.println(getY());
  Serial.print(" Current Heading: ");
  if (heading == 0)
    Serial.println("North");
  else if (heading == 1)
    Serial.println("East");
  else if (heading == 2)
    Serial.println("South");
  else if (heading == 3)
    Serial.println("West");
  else
    Serial.println("ERROR! Heading was not in range [0-3]");


  /* Print ASCII Art Map */
  //  String to_print = " _ _ _ _ _ _ _ _ _ ";
  //
  //  Serial.println(to_print);
  //
  //  /* Print middle of Grid*/
  //  for (byte y = 0; y < 8; y++) {
  //    to_print = "|";
  //    for (byte x = 0; x < 17; x++) {
  //      if ((x % 2) & getNthBit((x / 2), walls[y]) ) { // x is odd- check walls[0-8] for vertical walls
  //        to_print = String(to_print + "|");
  //      }
  //      else if (getNthBit(y, walls[(9 + (x % 2))])) { // x is even- check walls[9-17] for horizontal walls
  //        to_print = String(to_print + "_");
  //      }
  //      else {
  //        to_print = String(to_print + " ");
  //      }
  //    }
  //    to_print = String(to_print + "|");
  //    Serial.println(to_print);
  //  }
  //
  //  /* Print lower bounding wall of grid */
  //  to_print = "|";
  //  for (byte x = 0; x < 17; x++) {
  //    if ((x % 2) & getNthBit((x / 2), walls[8]) ) { // x is odd- check walls[0-8] for vertical walls
  //      to_print = String(to_print + "|");
  //    }
  //    else if (!(x % 2)) { // x is even- put down a horizontal wall
  //      to_print = String(to_print + "_");
  //    }
  //    else {
  //      to_print = String(to_print + " ");
  //    }
  //  }
  //  to_print = String(to_print + "|");
  //  Serial.println(to_print);

  // Print raw walls values
  Serial.print(" ");
  for (byte x = 9; x < 18; x++) {
    Serial.print(walls[x]);
    Serial.print(" ");
  }
  Serial.println("");
  for (byte x = 0; x < 9; x++) {
    Serial.println(walls[x]);
  }

}
