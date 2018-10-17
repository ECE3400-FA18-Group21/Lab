/*
 * @date: 10.17.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Used to complete Milestone 2 documentation
 */
#define NUM_SENSORS_ANALOG      3    //number of analog sensors used
#define NUM_SENSORS_DIGITAL     4    //number of digital sensors used 
#define THRESHOLD_ANALOG        500  //Threshold for line sensing
#define THRESHOLD_DIGITAL       1000 //Threshold for line sensing

 #include <Arduino.h>

/*
 * Returns an array of size NUM_SENSORS_ANALOG of either 1 or 0.
 * Each array element corresponds to the reading of one sensor.
 * If the sensor sees a line (based on [THRESHOLD_ANALOG]) it outputs 0,
 * and otherwise, it outputs 1. Reads from Arduino pins [A0,A1,A2]
 */
unsigned int * checkSensorsAnalog();

/*
 * Returns an array of size NUM_SENSORS_DIGITAL of either 1 or 0.
 * Each array element corresponds to the reading of one sensor.
 * If the sensor sees a line (based on [THRESHOLD_DIGITAL]) it outputs 0,
 * and otherwise, it outputs 1. Reads from Arduino pins [2, 3, 4, 9]
 */
unsigned int * checkSensorsDigital();
