/*
    Base Tractor Implement Header
    All Implements should be derived from this implementation
*/

#pragma once
#include <stdint.h>

const int  BUFFER_SIZE = 6;
const uint8_t START_BYTE = 0xAA;
const uint8_t END_BYTE = 0xFF;

// COMMANDS & RESPONSES uint8_tS
const uint8_t SET_POWER = 0x01;
const uint8_t GET_POWER = 0x02;
const uint8_t GET_FUEL = 0x03;

const int critical_fuel_level = 5;

class TractorImplement{

public:
   
   // Methods
    void            set_power(uint8_t mode);
    uint8_t         get_power();
    int             get_fuel_level();

    virtual void    read_message() = 0;
    void            process_packet(uint8_t packet[], int packet_len);
    virtual void    execute_command(uint8_t command, uint8_t data[], int data_len) = 0;
    void            check_if_fuel_critical();
    

protected:

    uint8_t         buffer[BUFFER_SIZE];
    bool            power;
    int             fuel_level;

};
