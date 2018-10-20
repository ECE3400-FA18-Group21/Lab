/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Benchmark Sensors
 */


/* Set up RF24 transceiver for transmit mode on Robot */
void RF24_tx_setup();

/* Send byte array of length n */
void RF24_tx_send(byte *msg, int n);

void RF24_rx_setup();

void RF24_rx_read();
