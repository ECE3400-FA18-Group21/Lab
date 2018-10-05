/*
 * @date: 09.27.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 */
#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
#define THRESHOLD 100 // bin thresholding for 660 Hz signal

#include <FFT.h>
#include <Arduino.h>
#include "mic.h"

void fft_setup(){
  TIMSK0 = 0;          // turn off timer0 for lower jitter - delay() and millis() killed
  ADCSRA = 0xe7;       // set the adc to free running mode, set prescaler=128 (default e5=32)
  ADMUX = 0x45;        // use adc5
  DIDR0 = 0x01;        // turn off the digital input for adc0
}

/**
 * [get_fft_bins] 
 * Runs the FFT operation using the FFT library
 * OUTPUT = FFT magnitude data in the form of a 128-bin byte array
 */
byte * get_fft_bins(){
    cli();                                  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 512 ; i += 2) {    // save 256 samples
      while(!(ADCSRA & 0x10));              // wait for adc to be ready
      ADCSRA = 0xf7;                        // restart adc --> set prescaler=f7=128 (default f5=32)
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

/**
 * [detect_660hz] 
 * OUTPUT = returns TRUE if a 660hz signal is detected by the Arduino,
 *          & FALSE otherwise
 * Uses THRESHOLD to determine whether the tone is playing or not
 */
bool detect_660hz(){
    byte * fft_log_out = get_fft_bins();
    if (fft_log_out[17] > THRESHOLD && fft_log_out[18] > THRESHOLD) //bins 18 & 19, but 0 based so subtract 1
        return true;
    else
        return false;
}
