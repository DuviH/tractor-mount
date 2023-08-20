
#include "SpiImplement.hpp"

#define SLAVE_READY_PIN 2
#define SLAVE_SELECT_PIN 10
volatile bool slaveReady=false;

void    SpiImplement::begin(){
    pinMode(SS, OUTPUT); // Set the SS pin as output
    SPI.begin();
    pinMode(SLAVE_SELECT_PIN, OUTPUT);
    digitalWrite(SLAVE_SELECT_PIN, HIGH);

    pinMode(SLAVE_READY_PIN, INPUT);
    // slave can signle when its ready/when its done by changing the SLAVE_READY_PIN
    attachInterrupt(digitalPinToInterrupt(SLAVE_READY_PIN), slaveIsReady, RISING);
    attachInterrupt(digitalPinToInterrupt(SLAVE_READY_PIN), slaveNotReady, FALLING);

}

void    SpiImplement::read_message(){
    int     bufferIndex = 0;
    uint8_t checksum = 0;

    while (!slaveReady){
        // might lead to deaedlock, implementing a timeout here might be a good idea
    }

    /* slave ready to send data
        read data until slave isn't ready again (packet done)
    */

    digitalWrite(SLAVE_SELECT_PIN, LOW);
    while (slaveReady){
        buffer[bufferIndex] = SPI.transfer(0x00);
        checksum ^= buffer[bufferIndex++];
    }
    
    digitalWrite(SLAVE_SELECT_PIN, HIGH);
    if (checksum != 0){
        // there was a check sum error
        // add error handeling here
    }
    process_packet(buffer, --bufferIndex);

}

void    SpiImplement::execute_command(uint8_t command, uint8_t data[], int data_len){

    uint8_t checksum = command;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(SLAVE_SELECT_PIN, LOW);
    SPI.transfer(command);
    for (int i = 0; i < data_len; i++) {
        SPI.transfer(data[i]);
        checksum ^= data[i];
    }
    SPI.transfer(checksum);
    digitalWrite(SLAVE_SELECT_PIN, HIGH); 
    SPI.endTransaction();

}

// ISR to handle the "ready" signal from the slave
void slaveIsReady() {
  slaveReady = true;
}

// ISR to handle the "not ready" signal from the slave
void slaveNotReady() {
  slaveReady = false;
}