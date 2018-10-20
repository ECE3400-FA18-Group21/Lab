/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Benchmark Sensors
 */
#include "maze.h"
#include <Arduino.h>

class MazeImpl : public Maze{
  private:
    byte walls[]; // Wall map representation and visited intersections
    byte pos; //Robot position. First 4 bits are x coord, Second 4 bits are y coord
    byte heading; //Robot direction (can be 0-3)
    short visited[]; // Represents all visited nodes. Each entry in the array is a different
                     // Row (y coordinate) and the first 9 bits are whether the corresponding
                     // x coordinate on the grid was visited. Will have 9 entries, so whole
                     // array takes 18 bytes.
  
  public:
    /*
     * turnLeft() tells the Maze object that the robot is turning left, and to adjust the 
     * representation accordingly.
     */
    void turnLeft(){
      int temp_heading = (int)heading;
      temp_heading = (temp_heading - 1) % 4;
      heading = (0xFF) & temp_heading; //convert to byte
    };
    /*
     * turnRight() tells the Maze object that the robot is turning right, and to adjust the 
     * representation accordingly.
     */
    void turnRight(){
      int temp_heading = (int)heading;
      temp_heading = (temp_heading + 1) % 4;
      heading = (0xFF) & temp_heading;
    };
    /*
     * advanceIntersection(frontWall, leftWall, rightWall) tells the Maze object that the robot 
     * has moved one square forward and sees the following walls adjacent to the square
     */
    void advanceIntersection(bool frontWall, bool leftWall, bool rightWall){
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
    };

    byte getX() {
      return (pos >> 4);
    };

    byte getY() {
      return (pos & 0x0F);
    };

    void getWallsAtCurrPos() {
      return walls[pos >> 4];
      
    
    }
};
