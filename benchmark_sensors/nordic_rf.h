#include <RF24.h>
#include <Arduino.h>

/* ======== ROBOT CODE =========*/

void robotSetup(RF24 radio);

void sendToBaseStation(RF24 radio);

/* ======== BASE STATION CODE =========*/

void baseStationSetup(RF24 radio);

void readFromRobot(RF24 radio);
