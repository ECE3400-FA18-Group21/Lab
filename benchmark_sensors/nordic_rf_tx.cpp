/* Should copy this sketch to local directory and test there before integrating with rest of code*/

#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0; //tx

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

//byte addresses[][6] = {"1Node","2Node"};
const uint64_t pipes[2] = {0x0000000042LL, 0x0000000043LL}; //team 21, left is the tx (robot), right is the rx (base station)


void setup() {
  Serial.begin(115200);
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing pipe for the Robot
  radio.openWritingPipe(pipes[0]);
  
}

void loop() {
  Serial.println("Start sending");
  byte test_msg[5] = "test";

  //transmit message, this will block 
   if (!radio.write( &test_msg, sizeof(byte) )){
     Serial.println(F("failed"));
   }

  //wait 2 sec
  delay(2000);
}


