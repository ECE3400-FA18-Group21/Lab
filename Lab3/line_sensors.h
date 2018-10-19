/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Benchmark Sensors
 */
#include <Arduino.h>

#define NUM_SENSORS             3  // number of sensors used
#define THRESHOLD               500 //Threshold for line sensing


/*
 * Returns an array of size NUM_SENSORS of either 1 or 0.
 * Each array element corresponds to the reading of one sensor.
 * If the sensor sees a line (based on [THRESHOLD]) it outputs 0,
 * and otherwise, it outputs 1. Reads from Arduino pins [A0,A1,A2]
 */
unsigned int * checkSensors();
