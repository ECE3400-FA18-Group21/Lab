/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 */
#define IR_THRESHOLD 100 // bin thresholding for 6.08 kHz signal

#include <Arduino.h>
#include "ir_hat.h"
#include "fft_util.h"

void fft_setup_ir(){
  fft_setup(0);
}

/**
 * [get_fft_bins] 
 * Runs the FFT operation using the FFT library
 * OUTPUT = FFT magnitude data in the form of a 128-bin byte array
 */
byte * get_fft_bins_ir(){
    return get_fft_bins(0);
}

/**
 * [detect_6080hz] 
 * OUTPUT = returns TRUE if a 6080hz signal is detected by the Arduino,
 *          & FALSE otherwise
 * Uses THRESHOLD to determine whether a nearby robot is detected 
 * (emitting IR at 6.08 kHz) or a decoy (emitting at 18 kHz)
 */
bool detect_6080hz(){
    byte * fft_log_out = get_fft_bins_ir();
    if (fft_log_out[40] > IR_THRESHOLD && fft_log_out[41] > IR_THRESHOLD) //bins 41 & 42, but 0 based so subtract 1
        return true;
    else
        return false;
}
