#include "TractorImplement.hpp"
#include <SoftwareSerial.h>

class Rs232Implement : public TractorImplement{

    public:
        Rs232Implement();
        Rs232Implement(uint8_t tx_pin, uint8_t rx_pin);

        void    begin(long baud);
        void    read_message();
        void    execute_command(uint8_t command, uint8_t data[], int data_len);

    private:
        SoftwareSerial  serial;

};