#include <Arduino.h>

#define NUM_SENSORS_ANALOG      3    //number of analog sensors used
#define NUM_SENSORS_DIGITAL     3    //number of digital sensors used 
#define THRESHOLD_ANALOG        500  //Threshold for line sensing
#define THRESHOLD_DIGITAL       100 //Threshold for line sensing


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
 * and otherwise, it outputs 1. Reads from Arduino pins [FILL IN DIGITAL PINS]
 */
unsigned int * checkSensorsDigital();
