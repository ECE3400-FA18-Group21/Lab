/*
   Dec 2014 - TMRh20 - Updated
   Derived from examples by J. Coliz <maniacbug@ymail.com>
*/
/**
 * Example for efficient call-response using ack-payloads 
 * 
 * This example continues to make use of all the normal functionality of the radios including 
 * the auto-ack and auto-retry features, but allows ack-payloads to be written optionlly as well. 
 * This allows very fast call-response communication, with the responding radio never having to 
 * switch out of Primary Receiver mode to send back a payload, but having the option to switch to 
 * primary transmitter if wanting to initiate communication instead of respond to a commmunication. 
 */
#include <SPI.h>                    //include basic SPI library
#include <nRF24L01.h>               //include RF24 libraries
#include <RF24.h>                   //include RF24 libraries
#include <printf.h>

//----------------------------------------------------------------------------------------------------//
//                                        USER CONFIG                                                 //
//----------------------------------------------------------------------------------------------------//
// Transmitter: radioNumber = 1
//    Receiver: radioNumber = 0
bool radioNumber = 0;

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
                                                             
// Use formula to determine what addresses your group should have
const uint64_t addresses[][2] = { 0x000000006ELL, 0x000000006FLL };

// Variable to store the instruction to send
byte instruction = 0b00000010;

void setup(){
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted_CallResponse"));

  // General setup & configuration for both radios
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads

  // TRANSMITTER SETUP
  if(radioNumber==1) {
    radio.openWritingPipe(addresses[0]);        
    radio.stopListening();
  }
  // RECEIVER SETUP
  else {
    radio.openReadingPipe(1,addresses[0]);      // Open a reading pipe on address 0, pipe 1
    radio.startListening();                     // Start listening  
    radio.writeAckPayload(1,&counter,1);        // Pre-load an ack-paylod into the FIFO buffer for pipe 1
  }
}
void loop(void) {
    //----------------------------------------------------------------------------------------------------//
    //                              TRANSMITTER - On Basestation                                          //
    //----------------------------------------------------------------------------------------------------//
    if(radioNumber == 1) {
      byte received_ackPayload;                               // Initialize a variable for the incoming response
      
      radio.stopListening();                                  // First, stop listening so we can talk.      
      Serial.print(F("Now sending "));
                                                    
      if (radio.write(&instruction, 1) ){                     // Send the instruction variable to the other radio 
          if(!radio.available()){                             // If nothing in the buffer, we got an ack but it is blank
              Serial.print(F("Got blank response"));    
          }else{      
              while(radio.available() ){                      // If an ack with payload was received
                  radio.read(&received_ackPayload, 1);        // Read it, and display the response time
                  
                  Serial.print(F("Got response "));
                  Serial.print(received_ackPayload);
              }
          }
      
      }
      else {        
        Serial.println(F("Sending failed.")); 
      }                                               
    delay(1000);  // Try again later
    }

    //----------------------------------------------------------------------------------------------------//
    //                                RECEIVER - On Basestation                                           //
    //----------------------------------------------------------------------------------------------------//
    else {
      byte pipeNo;
      byte msg; 
      byte ackPayload;                         
      while( radio.available(&pipeNo)){                       // Read all available payloads
        Serial.println(F("Radio Available."));
        radio.read(&msg, 1 ); 
        Serial.print(F("Loaded next response "));
        Serial.println(gotByte);                 
           
        // Since this is a call-response. Respond directly with an ack payload.
        // Ack payloads are much more efficient than switching to transmit mode to respond to a call
        ackPayload = 13;                                
        radio.writeAckPayload(pipeNo,&ackPayload, 1 );  
      }
    }
}
