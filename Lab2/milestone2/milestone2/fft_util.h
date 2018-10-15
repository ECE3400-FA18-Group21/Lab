/*
 * @date: 10.15.2018
 * @version: 02
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Used to complete Milestone 2
 */
 
/**
 * Sets up FFT for use with IR hat or microphone input.
 * [dev_select] is 1 to select microphone settings,
 *                    and 0 to select IR settings
 */
void fft_setup(int dev_select);

/**
 * Returns Byte array of FFT bins after running FFT.
 * [dev_select] is 1 to select microphone settings,
 *                    and 0 to select IR settings
 */
byte * get_fft_bins(int dev_select);
