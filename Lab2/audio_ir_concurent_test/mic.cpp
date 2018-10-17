/*
 * @date: 10.04.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Used to complete Lab 2 documentation
 */
#define MIC_THRESHOLD 100 // bin thresholding for 660 Hz signal

#include <Arduino.h>
#include "mic.h"
#include "fft_util.h"

void fft_setup_mic(){
  fft_setup(1);
}

/**
 * [get_fft_bins] 
 * Runs the FFT operation using the FFT library
 * OUTPUT = FFT magnitude data in the form of a 128-bin byte array
 */
byte * get_fft_bins_mic(){
    return get_fft_bins(1);
}

/**
 * [detect_660hz] 
 * OUTPUT = returns TRUE if a 660hz signal is detected by the Arduino,
 *          & FALSE otherwise
 * Uses THRESHOLD to determine whether the tone is playing or not
 */
bool detect_660hz(){
    byte * fft_log_out = get_fft_bins_mic();
    if (fft_log_out[17] > MIC_THRESHOLD && fft_log_out[18] > MIC_THRESHOLD) //bins 18 & 19, but 0 based so subtract 1
        return true;
    else
        return false;
}
