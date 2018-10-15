/*
 * @date: 10.15.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 */
 
/**
 * [read_range_sensor] reads [pin] and returns the raw rangefinder sensor reading
 */
int read_range_sensor(int pin);

/**
 * [detect_wall_6in] returns true if a wall is about 6 inches from the robot
 * and false if it is much closer than 6 inches or much farther than 6 inches.
 * [pin] is the analog pin to read from.
 */
bool detect_wall_6in(int pin);


/**
 * [detect_wall_2in] returns true if a wall is about 2 inches from the robot
 * and false if it is much closer than 2 inches or much farther than 2 inches.
 * [pin] is the analog pin to read from.
 */
bool detect_wall_3in(int pin);
