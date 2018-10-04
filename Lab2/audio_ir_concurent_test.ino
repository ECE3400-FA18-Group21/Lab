#include "mic.cpp"
#include "ir_hat.cpp"

// setup found at https://www.instructables.com/id/Arduino-Timer-Interrupts/

int state = 0;

void setup() {
  pinMode(7, OUTPUT);  //set pins as output to toggle leds
  pinMode(8, OUTPUT);


  cli(); //stop interrupts for configuration

  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei(); //allow interrupts

}

ISR(TIMER0_COMPA_vect){
  // everytime the timer interrupt occurs, switch between check states (audio or ir)
  if(state){
    state = 0;
    //write pin high if 660Hz sound is detected
    digitalWrite(8, mic.detect_660hz());
  }
  else{
    state = 1;
    //write pin high if 6kHz ir signal is detected
    digitalWrite(7, ir_hat.detect_6008hz());
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
