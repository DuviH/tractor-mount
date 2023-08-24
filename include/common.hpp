#pragma once
// ########## Choose Implements #################
// Choose which implements to include
#define RS232_IMPLEMENT
#define SPI_IMPLEMENT
// ###########   Set Params    ###################
#define SERIAL_BAUD 9600 // baud rate with the upper-level application
#define MAX_SERVER_COMMAND_LEN 6
// ##############################################

#ifdef RS232_IMPLEMENT
#define RS232_TXPIN 9 // tx pin for the rs232 implement
#define RS232_RXPIN 8 // rx pin for the rs232 implement
#define RS232_BAUD 9600 // baud rate with the rs232 implement
#endif

#ifdef SPI_IMPLEMENT
#define SLAVE_READY_PIN 2
#define SLAVE_SELECT_PIN 10
#endif