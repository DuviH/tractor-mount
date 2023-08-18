
#include "SpiImplement.hpp"

void    SpiImplement::begin(){
    Serial1.begin(9600);
}

void    SpiImplement::execute_command(byte command, byte data[], int data_len){

    byte checksum = START_BYTE ^ command;
    Serial.write(START_BYTE);
    Serial.write(command);
    for (int i = 0; i < data_len; i++) {
        Serial.write(data[i]);
        checksum ^= data[i];
    }
    Serial.write(checksum);
    Serial.write(END_BYTE);

}