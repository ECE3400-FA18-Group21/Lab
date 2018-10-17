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
};
