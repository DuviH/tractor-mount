#include "server.hpp"
#include "common.hpp"

#ifdef RS232_IMPLEMENT
#include "Rs232Implement.hpp"
Rs232Implement rs232_implement(RS232_TXPIN, RS232_RXPIN);
#endif

#ifdef SPI_IMPLEMENT
#include "SpiImplement.hpp"
SpiImplement spi_implement(SLAVE_SELECT_PIN, SLAVE_READY_PIN);
#endif

void    ImplementsServer::begin(){

    #ifdef PERIODIC_FUEL_CHECK
    cli(); // stop interrupts
    set_periodic_isr();
    #endif

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

    #ifdef PERIODIC_FUEL_CHECK
    sei(); // allow interrupts
    #endif
}


void    ImplementsServer::get_command(){
    // Read from USB Serial (Upper Level Application)
    while (Serial.available() > 0) {
        char curr_char = (char)Serial.read();
        server_command += curr_char;
        
        if (curr_char == '\n' || curr_char == '\r'){
        command_done = true;
        }
    } 
  
    if (command_done){
        Serial.println(server_command); // Echo the command
        parse_command(server_command);
        server_command = "";            // Clear the command
        command_done = false;      // Reset command done flag
    }
}


void    ImplementsServer::parse_command(String command_string){

    unsigned int start = 0;
    unsigned int word_count = 0;
    String words[MAX_SERVER_COMMAND_LEN];

    for (unsigned int i = 0; i <= command_string.length(); i++) {
        if (i != command_string.length() && command_string.charAt(i) != ' ' && command_string.charAt(i) != '\t') {
        continue;
        }
        if (i > start){
            words[word_count++] = command_string.substring(start, i);
        }
        
        start = i + 1;
    }

    if (word_count < 3){
        Serial.println("Malformed command!");
        return;
    }

    TractorImplement* implement = nullptr;
    // word 1: implement name
    #ifdef SPI_IMPLEMENT
    if (words[0] == "spi" || words[0] == "Spi" || words[0] == "SPI"){
        implement = &spi_implement;
    }
    #endif
    #ifdef RS232_IMPLEMENT
    if (words[0] == "rs232" || words[0] == "Rs232" || words[0] == "RS232"){
        implement = &rs232_implement;
    }
    #endif
    // invalid implement check
    if (implement == nullptr){
        return;
    }
    // word 2: set/get command
    // word 3: command type
    // word 4-: command params

    // invalid command type check
    if (words[1] != "set" && words[1] != "get"){
        return;
    }

    if (words[1] == "set"){
        if (words[2] == "power"){
            if (word_count != 4){
                Serial.println("missing power mode!");
                return;
            }
            Serial.print("setting ");
            Serial.print(words[0]);
            Serial.print(" power ");
            Serial.println(words[3]);
            implement->set_power(uint8_t(words[3] == "on" ? 1 : 0));
        }
        return;
    }
    if (words[1] == "get"){
        if (words[2] == "power"){
            uint8_t power = implement->get_power();
            Serial.print(words[0]);
            Serial.print("'s power: ");
            Serial.println(power ? "on" : "off");
        }
        if (words[2] == "fuel"){
            int fuel_level = implement->get_fuel_level();
            Serial.print(words[0]);
            Serial.print("'s fuel level: ");
            Serial.println(fuel_level);
        }
        return;

    }


}


void    ImplementsServer::set_periodic_isr(){

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
}

// Set the ISR for the periodic fuel check
#ifdef PERIODIC_FUEL_CHECK
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
#endif