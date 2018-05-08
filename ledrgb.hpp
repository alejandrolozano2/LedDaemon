#ifndef LEDRGB_H
#define LEDRGB_H

#include "leds.hpp"
#include <vector>



class LEDRGB
{

public:

    typedef enum
    {
        eRED,
        eGREEN,
        eBLUE
    }eLED_t;


    LEDRGB();
    LEDRGB(std::string  r, std::string  g, std::string  b );
    void setBrightnessLED(eLED_t, int ) ; 
    void setBrightness(int );

private:
    LED RGB[3];
};




#endif 