// Include necessary libraries
#include <Arduino.h>
#include <SPI.h>

// ########## Choose Implements #################
// Choose which implements to include
#define RS232_IMPLEMENT
#define SPI_IMPLEMENT

// ##############################################

#ifdef RS232_IMPLEMENT
#include "Rs232Implement.hpp"
Rs232Implement rs232_implement;
#endif

#ifdef SPI_IMPLEMENT
#include "SpiImplement.hpp"
SpiImplement spi_implement;
#endif

void setup() {

  // Initialize communication with the upper level application
  Serial.begin(9600); // Configure USB Serial at 9600 baud

  // Initialize communication with the RS-232 implement
  #ifdef RS232_IMPLEMENT
  rs232_implement.begin();.begin(9600); // Configure Serial1 at 9600 baud
  #endif

  // SPI setup (as master)
  #ifdef SPI_IMPLEMENT
  spi_implement.begin();
  #endif


}

void loop() {
  // Read from USB Serial (Upper Level Application)
  if (Serial.available()) {
    char c = Serial.read();
    Serial.print("Received from PC: ");
    Serial.println(c);
  }

  // Read from RS-232 (RS232 Implement)
  #ifdef RS232_IMPLEMENT
  if (Serial1.available()) {
    char c = Serial1.read();
    // Process RS-232 data
  }
  #endif

}

#ifdef SPI_IMPLEMENT
ISR(SPI_STC_vect) {
  // ... SPI code as before ...
}
#endif