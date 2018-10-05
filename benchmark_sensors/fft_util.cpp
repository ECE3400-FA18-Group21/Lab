#define LOG_OUT 1     // use the log output function
#define FFT_N 256     // set to 256 point fft
/*
 * @date: 10.04.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Used to complete Lab 2 documentation
 */
#include <FFT.h>
#include <Arduino.h>
#include "fft_util.h"

void fft_setup(int dev_select){
      TIMSK0 = 0;          // turn off timer0 for lower jitter - delay() and millis() killed
      if(dev_select==1){
        ADCSRA = 0xe7;     // set the adc to free running mode, set prescaler = 128 for microphone
        ADMUX = 0x45;      // use adc0 for mic
      }else{
        ADCSRA = 0xe5;     // set the adc to free running mode, set prescaler = 32 for ir
        ADMUX = 0x44;      // use adc4 for ir
      }
      DIDR0 = 0x01;        // turn off the digital input for adc0
}


byte * get_fft_bins(int dev_select){
    cli();                                  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 512 ; i += 2) {    // save 256 samples
      while(!(ADCSRA & 0x10));              // wait for adc to be ready
      if(dev_select==1)
        ADCSRA = 0xf7;                      // restart adc --> set prescaler=f5=128 if MIC
      else
        ADCSRA = 0xf5;                      // restart adc --> set prescaler=f5=32  if IR
      byte m = ADCL;                        // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m;                 // form into an int
      k -= 0x0200;                          // form into a signed int
      k <<= 6;                              // form into a 16b signed int
      fft_input[i] = k;                     // put real data into even bins
      fft_input[i+1] = 0;                   // set odd bins to 0
    }
    
    // window data, then reorder, then run, then take output
    fft_window();                           // window the data for better frequency response
    fft_reorder();                          // reorder the data before doing the fft
    fft_run();                              // process the data in the fft
    fft_mag_log();                          // take the output of the fft
    sei();                                  // turn interrupts back on
    return fft_log_out;
}
