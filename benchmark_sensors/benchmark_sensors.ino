#include "mic.h"
/*
 * @date: 09.27.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 */
int counter = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 
  fft_setup();
}

void loop() {
  int count = 0;
  Serial.println(detect_660hz());
  if(detect_660hz())
    counter++;
  else
    counter = 0;
  if(counter>6)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}

