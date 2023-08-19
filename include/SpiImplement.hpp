#include "TractorImplement.hpp"
#include <SPI.h>

class SpiImplement : public TractorImplement{

    public:

        void    begin();
        void    read_message();
        void    execute_command(uint8_t command, uint8_t data[], int data_len);

};