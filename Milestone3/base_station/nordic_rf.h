/*
   @date: 11.18.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Base Station - Milestone 4
*/
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

//--------------------------------------------------------//
//              TRANSMITTER - Robot                       //
//--------------------------------------------------------//
/* Set up RF24 transceiver for transmit mode on Robot */
void RF24_tx_setup(RF24 radio);

/* Send byte array of length n */
void RF24_tx_send(RF24 radio, byte *msg);

/* Send insturction 0b00000000 */
void send_turn_left(RF24 radio);

/* Send insturction 0b00000001 */
void send_turn_right(RF24 radio);

/**
   Send insturction 0b000XYZ10
   X = rightWall
   Y = leftWall
   Z = frontWall
*/
void send_advance_intersection(RF24 radio, bool frontWall, bool leftWall, bool rightWall);

/** Send instruction about treasure detection */
void send_treasure(RF24 radio, int bit2, int bit1, int bit0);

//--------------------------------------------------------//
//              RECEIVER - Base Station                   //
//--------------------------------------------------------//
/* Set up RF24 transceiver for receive mode on Base Station */
void RF24_rx_setup(RF24 radio);

/* Read data if available */
byte RF24_rx_read(RF24 radio);
