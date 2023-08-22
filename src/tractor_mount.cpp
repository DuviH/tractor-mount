
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
#define SLAVE_READY_PIN 2
#define SLAVE_SELECT_PIN 10
SpiImplement spi_implement(SLAVE_SELECT_PIN, SLAVE_READY_PIN);
#endif

void setup() {
  cli(); // stop interrupts
  // setup a time based interrupt to check fuel level periodicly
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

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

  sei(); // allow interrupts
}

void loop() {
  // Read from USB Serial (Upper Level Application)
  if (Serial.available() > 0) {
    byte curr_byte = Serial.read();
    Serial.print(curr_byte);
    
  }

}
volatile unsigned short count_secs=0;
ISR(TIMER1_COMPA_vect){
  // timer interrupt to check fuel
  // do that once every 10 seconds
  if (count_secs++ < 10){
    return;
  }
  count_secs = 0;

  #ifdef RS232_IMPLEMENT
  rs232_implement.check_if_fuel_critical();
  #endif

  #ifdef SPI_IMPLEMENT
  spi_implement.check_if_fuel_critical();
  #endif
  
}