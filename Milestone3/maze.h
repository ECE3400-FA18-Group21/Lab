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
    short visited[9]; // Represents all visited nodes. Each entry in the array is a different
                     // Row (y coordinate) and the first 9least significantare whether the corresponding
                     // x coordinate on the grid was visited. Will have 9 entries, so whole
                     // array takes 18 bytes.
                     
    byte walls[18]; // Wall map representation and visited intersections

    byte dfs_stack[81]; // Stores positions that have been visited (return path)
    byte stack_ptr; // Pointer for stack head

    
    /*
     * getAbsoluteCoord(byte dir return)s the absolute coordinate that is relative direction [dir] from the robot
     * dir is encoding as 0,1, or 2
     * 0 -> Straight ahead
     * 1 -> Left
     * 2 -> Right
     * 
     * WARNING: Does not check if new coordinates are in bounds
     */
    byte getAbsoluteCoord(byte dir);

    
    /*
     * isVisited Checks if coord was visited or not.
     */
    bool isVisited(byte coord);
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

    
    /*
       getNextCommand(frontWall, leftWall, rightWall) tells the robot which direction to turn.
       returns: 0 to go straight
                1 to turn left
                2 to turn right
                3 to turn around
                
    */
    byte getNextCommand(bool frontWall, bool leftWall, bool rightWall);

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
