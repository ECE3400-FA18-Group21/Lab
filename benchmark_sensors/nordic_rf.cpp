#include "nordic_rf.h"

#define BASE_STATION_ADDR 66
#define ROBOT_ADDR 67
/* ======== ROBOT CODE =========*/

void robotSetup(RF24 radio){
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(BASE_STATION_ADDR);
}

void sendToBaseStation(RF24 radio){
  
}

/* ======== BASE STATION CODE =========*/

void baseStationSetup(RF24 radio){
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, ROBOT_ADDR);
  radio.startListening();
}

void readFromRobot(RF24 radio){
  if(radio.available()){
    //radio.read();
  }
  else{
    
  }
}
