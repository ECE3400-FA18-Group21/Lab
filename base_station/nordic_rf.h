/*
   @date: 10.21.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Base Station Program - Lab3
*/

#include <SPI.h>
#include <RF24.h>

/* Set up RF24 transceiver for transmit mode on Robot */
void RF24_tx_setup(RF24 radio);

/* Send byte array of length n */
void RF24_tx_send(RF24 radio, byte *msg);

/* Set up RF24 transceiver for receive mode on Base Station */
void RF24_rx_setup(RF24 radio);

/* Read data if available */
byte RF24_rx_read(RF24 radio);
