
#include "SpiImplement.hpp"

void    SpiImplement::begin(){
    SPI.begin();
}

void    SpiImplement::execute_command(uint8_t command, uint8_t data[], int data_len){

    uint8_t checksum = START_BYTE ^ command;
    SPI.transfer(START_BYTE);
    SPI.transfer(command);
    for (int i = 0; i < data_len; i++) {
        SPI.transfer(data[i]);
        checksum ^= data[i];
    }
    SPI.transfer(checksum);
    SPI.transfer(END_BYTE);

}