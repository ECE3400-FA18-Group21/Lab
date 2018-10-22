/*
   @date: 10.21.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Base Station Program - Lab 3
*/

#include "nordic_rf.h"
#include <Arduino.h>

// 6ELL is Robot, 6FLL is base station
const uint64_t addresses[][2] = {0x000000006ELL, 0x000000006FLL};

//--------------------------------------------------------//
//              TRANSMITTER - Robot                       //
//--------------------------------------------------------//
/* Set up RF24 transceiver for transmit mode on Robot */
void RF24_tx_setup(RF24 radio) {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); // Set radio to max power level
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.openWritingPipe(addresses[0]);        // Create a writing pipe for the robot
  radio.stopListening();
}

/* Send byte array of length n */
void RF24_tx_send(RF24 radio, byte *msg) {
  Serial.println("Trying to send");
  if (!radio.write( msg, 1)) {
    Serial.println(F("failed"));
  }
}
void send_turn_left(RF24 radio){
  byte instruction = 0b00000000;
  RF24_tx_send(radio, &instruction);
}
void send_turn_right(RF24 radio){
  byte instruction = 0b00000001;
  RF24_tx_send(radio, &instruction);  
}
void send_advance_intersection(RF24 radio, bool frontWall, bool leftWall, bool rightWall){
  byte instruction = 0b00000010;
  if(frontWall)
    instruction = instruction | 0b00000100;
  if(leftWall)
    instruction = instruction | 0b00001000;
  if(frontWall)
    instruction = instruction | 0b00010000;
  RF24_tx_send(radio, &instruction); 
}

//--------------------------------------------------------//
//              RECEIVER - Base Station                   //
//--------------------------------------------------------//
/* Set up RF24 transceiver for receive mode on Base Station */
void RF24_rx_setup(RF24 radio) {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); // Set radio to max power level
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.openReadingPipe(1, addresses[0]);       // Open a reading pipe on address 0, pipe 1
  radio.startListening();                       // Start listening
}

/* Read data if available */
byte RF24_rx_read(RF24 radio) {

  byte pipe, msg;                          // Declare variables for the pipe and the byte received
  while ( radio.available(&pipe)) {            // Read pipe 1
    radio.read( &msg, 1 );
    Serial.print(F("Loaded next response "));
    Serial.println(msg);
  }
  return msg;
}
