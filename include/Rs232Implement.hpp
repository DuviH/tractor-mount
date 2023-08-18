#include "TractorImplement.hpp"

class Rs232Implement : public TractorImplement{

    void    begin();
    void    execute_command(byte command, byte data[], int data_len);

};