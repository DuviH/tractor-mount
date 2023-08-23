
#include "common.hpp"
#include "SpiImplement.hpp"

volatile bool   slaveReady=false;

SpiImplement::SpiImplement(){
    slave_select = 10;
    slave_ready = 2;
}

SpiImplement::SpiImplement(int slave_select_pin, int slave_ready_pin){
    slave_select = slave_select_pin;
    slave_ready = slave_ready_pin;
}

void    SpiImplement::begin(){
    pinMode(SS, OUTPUT); // Set the SS pin as output
    SPI.begin();
    pinMode(slave_select, OUTPUT);
    digitalWrite(slave_select, HIGH);

    pinMode(slave_ready, INPUT_PULLUP);
    // slave can signle when its ready/when its done by changing the SLAVE_READY_PIN
    attachInterrupt(digitalPinToInterrupt(slave_ready), slaveChanged, CHANGE);

}

void    SpiImplement::read_message(){
    int     bufferIndex = 0;
    uint8_t checksum = 0;

    unsigned long countTime = 0; // count
    unsigned long timeout = 3000; // 3 seconds

    while (!slaveReady){
        
        if (countTime >= timeout) {
            
            return; 
        }
        
        delay(100);
        countTime += 100;
    }

    /* slave ready to send data
        read data until slave isn't ready again (packet done)
    */

    digitalWrite(slave_select, LOW);

    while (slaveReady){
        buffer[bufferIndex] = SPI.transfer(0x00);
        checksum ^= buffer[bufferIndex++];
    }
    
    digitalWrite(slave_select, HIGH);
    if (checksum != 0){
        // there was a check sum error
        // add error handeling here
    }
    process_packet(buffer, --bufferIndex);

}

void    SpiImplement::execute_command(uint8_t command, uint8_t data[], int data_len){

    uint8_t checksum = command;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(slave_select, LOW);
    SPI.transfer(command);
    for (int i = 0; i < data_len; i++) {
        SPI.transfer(data[i]);
        checksum ^= data[i];
    }
    SPI.transfer(checksum);
    digitalWrite(slave_select, HIGH); 
    SPI.endTransaction();

}

// ISR to handle the "ready" signal from the slave
void slaveChanged() {
  slaveReady = !slaveReady;
}