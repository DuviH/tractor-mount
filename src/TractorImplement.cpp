/*
    Base Tractor Implement
    All Implements should be derived from this implementation
*/
#include "common.hpp"
#include "TractorImplement.hpp"

void TractorImplement::set_power(uint8_t mode){

    uint8_t data[] = { mode };
    int length = sizeof(data) / sizeof(data[0]);

    execute_command(SET_POWER, data, length);
}

uint8_t TractorImplement::get_power(){
    uint8_t data[] = {};
    execute_command(GET_POWER, data, 0);
    read_message();

    return power;
    
}

int TractorImplement::get_fuel_level(){

    uint8_t data[] = {};
    execute_command(SET_POWER, data, 0);
    read_message();

    return fuel_level;
}

void TractorImplement::process_packet(uint8_t packet[], int packet_len){
    // packet_len can be usefull for future use if other commands allow unknown data lens
    switch(packet[0]){
        case SET_POWER:
            //ACQ FOR POWER SET COMMAND
            break;

        case GET_POWER:
            power = bool(packet[1]);
            break;

        case GET_FUEL:
            fuel_level = 0;
            fuel_level = (unsigned int) packet[1] << 24;
            fuel_level |= (unsigned int) packet[2] << 16;
            fuel_level |= (unsigned int) packet[3] << 8;
            fuel_level |= packet[4];
            break;
        default:
            break;
    }
}

void TractorImplement::check_if_fuel_critical(){
    if(get_fuel_level() < critical_fuel_level){
        set_power(false);
    }
}