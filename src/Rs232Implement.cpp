
#include "Rs232Implement.hpp"

void    Rs232Implement::begin(){
    Serial1.begin(9600);
}

void    Rs232Implement::execute_command(byte command, byte data[], int data_len){

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