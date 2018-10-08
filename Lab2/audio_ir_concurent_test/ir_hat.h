/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 */
 
/**
 * [fft_setup] sets up the registers used by the FFT library
 *   These registers are set as follows:
 *   [TIMSK0] (Timer0) = 0 (Turns off Timer 0 to decrease noise)
 *   [ADCSRA] (ADC control register) = 0xe5 (Sets ADC to free running mode,
 *                                         with a prescaler of 32)
 *   [ADMUX] (ADC mux select) = 0x40 (use ADC0)
 *   [DIDR0] (Digital input select) = 0x01 (disable digital input for adc0)
 */
void fft_setup_ir();

/**
 * [get_fft_bins] 
 * Runs the FFT operation using the FFT library
 * OUTPUT = FFT magnitude data in the form of a 128-bin byte array
 */
byte * get_fft_bins_ir();

/**
 * [detect_6008hz] 
 * OUTPUT = returns TRUE if a 6008hz signal is detected by the Arduino,
 *          & FALSE otherwise
 * Uses THRESHOLD to determine whether a nearby robot is detected 
 * (emitting IR at 6.08 kHz) or a decoy (emitting at 18 kHz)
 */
bool detect_6080hz();
