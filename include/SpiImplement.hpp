#include <Arduino.h>
#include "TractorImplement.hpp"

class SpiImplement : public TractorImplement{

    void    begin();
    void    execute_command(byte command, byte data[], int data_len);

};