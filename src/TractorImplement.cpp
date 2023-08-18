/*
    Base Tractor Implement
    All Implements should be derived from this implementation
*/
#include "TractorImplement.hpp"

// TODO: implement constructors
//TractorImplement:

void TractorImplement::set_power(byte mode){

    uint8_t data[] = { mode };
    int length = sizeof(data) / sizeof(data[0]);

    execute_command(SET_POWER, data, length);
}

byte TractorImplement::get_power(){
    return power;
}
