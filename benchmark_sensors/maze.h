/*
 * The Maze class represents a maze for the ECE 3400 class
 */
class Maze{
  public:
    /*
     * turnLeft() tells the Maze object that the robot is turning left, and to adjust the 
     * representation accordingly.
     */
    virtual void turnLeft() = 0;
    /*
     * turnRight() tells the Maze object that the robot is turning right, and to adjust the 
     * representation accordingly.
     */
    virtual void turnRight() = 0;
    
    /*
     * advanceIntersection(frontWall, leftWall, rightWall) tells the Maze object that the robot 
     * has moved one square forward and sees the following walls adjacent to the square
     */
    virtual void advanceIntersection(bool frontWall, bool leftWall, bool rightWall) = 0;
};
