/*
   @date: 10.21.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Base Station Program - Lab3
*/
#include <Arduino.h>

/*
   The Maze class represents a maze for the ECE 3400 class
*/
class Maze {
  private:
    byte pos; //Robot position. First 4 bits are x coord, Second 4 bits are y coord
    byte heading; //Robot direction (can be 0-3)
    short visited[]; // Represents all visited nodes. Each entry in the array is a different
                     // Row (y coordinate) and the first 9 bits are whether the corresponding
                     // x coordinate on the grid was visited. Will have 9 entries, so whole
                     // array takes 18 bytes.
                     
    byte walls[]; // Wall map representation and visited intersections
  public:
    Maze();
    /*
       turnLeft() tells the Maze object that the robot is turning left, and to adjust the
       representation accordingly.
    */
    void turnLeft() ;
    /*
       turnRight() tells the Maze object that the robot is turning right, and to adjust the
       representation accordingly.
    */
    void turnRight() ;

    /*
       advanceIntersection(frontWall, leftWall, rightWall) tells the Maze object that the robot
       has moved one square forward and sees the following walls adjacent to the square
    */
    void advanceIntersection(bool frontWall, bool leftWall, bool rightWall) ;
    /*
       TODO: Add navigation commands for robot and treasure detection
    */

    /* Returns the current x position of the robot */
    byte getX() ;

    /* Returns the current y position of the robot */
    byte getY() ;

    /*
       getGUIMessage(x, y) returns the message to send to the basestation GUI based on
       x and y coordinate
    */
    String getGUIMessage(byte x, byte y);

    /*
       printInfo() prints out the current maze representation state to the serial monitor
    */
    void printInfo() ;
};
