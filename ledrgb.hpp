#ifndef LEDRGB_H
#define LEDRGB_H

#include "leds.hpp"
#include <vector>

typedef  std::vector<LED> LED_STRIP_CONTAINER;

class LEDRGB: public LED_STRIP_CONTAINER
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
    void open(eLED_t, std::string);

};




#endif 