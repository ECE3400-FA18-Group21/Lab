/*
 * @date: 12.03.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * CODE FOR FINAL COMPETITION
 */
 
/**
 * [fft_setup] sets up the registers used by the FFT library
 *   These registers are set as follows:
 *   [TIMSK0] (Timer0) = 0 (Turns off Timer 0 to decrease noise)
 *   [ADCSRA] (ADC control register) = 0xe7 (Sets ADC to free running mode,
 *                                         with a prescaler of 128)
 *   [ADMUX] (ADC mux select) = 0x40 (use ADC0)
 *   [DIDR0] (Digital input select) = 0x01 (disable digital input for adc0)
 */
void fft_setup_mic();

/**
 * [get_fft_bins] 
 * Runs the FFT operation using the FFT library
 * OUTPUT = FFT magnitude data in the form of a 128-bin byte array
 */
byte * get_fft_bins_mic();

/**
 * [detect_660hz] 
 * OUTPUT = returns TRUE if a 660hz signal is detected by the Arduino,
 *          & FALSE otherwise
 * Uses THRESHOLD to determine whether the tone is playing or not
 */
bool detect_660hz();
