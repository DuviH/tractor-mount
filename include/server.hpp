/*
    the server holds several implements
    takes commands from the upper level application
    sends commands to the implements & gets telemetry from them
*/
#include <Arduino.h>
#include "TractorImplement.hpp"


#define PERIODIC_FUEL_CHECK

class ImplementsServer{

    public:

        void    begin();
        void    get_command();

    private:
        void    set_periodic_isr();
        void    parse_command(String command_string);
        
        String  server_command = "";
        bool    command_done = false;

};