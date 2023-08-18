
# include <string>

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

