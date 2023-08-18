
# include <string>
#include "mocks.hpp"
#include <arduino>
class implement_mock{

    public:
        implement_mock(string mock_name, bool state = false, float fuel = 100);

        string  name;
        bool    power;
        float   fuel_level;

        bool    get_power_state(); 
        void    set_power_state(bool state);
        float   get_fuel_level();
        

    private:
        void    set_fuel_level(); // simulates fuel level changing


}

implement_mock::implement_mock(string mock_name, bool state, float fuel){
    
    name = mock_name;
    power = state;
    fuel_level = fuel;

}

bool implement_mock::get_power_state(){

}

setup()