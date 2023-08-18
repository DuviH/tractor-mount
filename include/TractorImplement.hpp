/*
    Base Tractor Implement Header
    All Implements should be derived from this implementation
*/

#pragma once
#include <Arduino.h>

const byte START_BYTE = 0xAA;
const byte END_BYTE = 0xFF;

// COMMANDS & RESPONSES BYTES

const byte SET_POWER = 0x01;
const byte GET_POWER = 0x02;
const byte GET_FUEL = 0x03;

const int critical_fuel_level = 5;

class TractorImplement{

public:

    // Constructors
    /*
    take fuel and power into account    
    */
   
   // Methods
    void            set_power(byte mode);
    byte            get_power();
    int             get_fuel_level();

    virtual void    begin() = 0;
    virtual void    execute_command(byte command, byte data[], int data_len) = 0;
    void            check_if_fuel_critical()
    

protected:

    bool            power;
    int           fuel_level;

};
