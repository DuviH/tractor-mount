
// ########## Choose Implements #################
// Choose which implements to include
#define RS232_IMPLEMENT
#define SPI_IMPLEMENT

// ##############################################
#include "TractorImplement.hpp"

#define SERIAL_BAUD 9600 // baud rate with the upper-level application

#ifdef RS232_IMPLEMENT
#include "Rs232Implement.hpp"
#define RS232_TXPIN 9 // tx pin for the rs232 implement
#define RS232_RXPIN 8 // rx pin for the rs232 implement
#define RS232_BAUD 9600 // baud rate with the rs232 implement
Rs232Implement rs232_implement(RS232_TXPIN, RS232_RXPIN);
#endif

#ifdef SPI_IMPLEMENT
#include "SpiImplement.hpp"
SpiImplement spi_implement;
#endif

void setup() {

  // Initialize communication with the upper level application
  Serial.begin(SERIAL_BAUD); // begin USB Serial communication

  // Initialize communication with the RS-232 implement
  #ifdef RS232_IMPLEMENT
  rs232_implement.begin(RS232_BAUD); // begin rs232 Serial communication
  #endif

  // SPI setup (as master)
  #ifdef SPI_IMPLEMENT
  spi_implement.begin(); // begin SPI communication
  #endif


}

void loop() {
  // Read from USB Serial (Upper Level Application)
  if (Serial.available()) {
    byte curr_byte = Serial.read();
    if (curr_byte == START_BYTE) {
      // handle upper level command

    }
    
  }

  // Read from RS-232 (RS232 Implement)
  #ifdef RS232_IMPLEMENT
  // if (Serial1.available()) {
  //   char c = Serial1.read();
  //   // Process RS-232 data
  // }
  #endif

}

#ifdef SPI_IMPLEMENT
// ISR(SPI_STC_vect) {
//   // ... SPI code as before ...
// }
#endif