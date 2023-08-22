#include "TractorImplement.hpp"
#include <SPI.h>

class SpiImplement : public TractorImplement{

    public:

        SpiImplement();
        SpiImplement(int slave_select_pin, int slave_ready_pin);

        void    begin();
        void    read_message();
        void    execute_command(uint8_t command, uint8_t data[], int data_len);

    private:
        int     slave_select;
        int     slave_ready;

};

void    slaveChanged();