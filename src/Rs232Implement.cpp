
#include "Rs232Implement.hpp"

Rs232Implement::Rs232Implement(): serial(0, 1){}

Rs232Implement::Rs232Implement(uint8_t tx_pin, uint8_t rx_pin): serial(rx_pin, tx_pin){}

void    Rs232Implement::begin(long baud){
    serial.begin(baud);
}

void    Rs232Implement::read_message(){
    bool    readingPacket;
    int     bufferIndex;
    uint8_t checksum = 0;

    while (serial.available()) {
        uint8_t curr_byte = serial.read();

        // packet ended, process it
        if (curr_byte == END_BYTE) {
            readingPacket = false;
            // xor on my checksum & the sent checksum should be 0
            if (checksum != 0){
                // there was a check sum error
                // add error handeling here
            }
            // prosses the message, ignore the checksum
            process_packet(buffer, --bufferIndex);
            continue;
        }
        // calculate checksum
        checksum ^= curr_byte;

        // packet beginning reset buffer index
        if (curr_byte == START_BYTE) {
            readingPacket = true;
            bufferIndex = 0;
            continue;
        } 
        if (readingPacket) {
            buffer[bufferIndex++] = curr_byte;
        }
  }
}

void    Rs232Implement::execute_command(uint8_t command, uint8_t data[], int data_len){

    uint8_t checksum = START_BYTE ^ command;
    serial.write(START_BYTE);
    serial.write(command);
    for (int i = 0; i < data_len; i++) {
        serial.write(data[i]);
        checksum ^= data[i];
    }
    serial.write(checksum);
    serial.write(END_BYTE);

}