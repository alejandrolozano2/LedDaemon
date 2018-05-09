#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include "leds.hpp"
#include <vector>

typedef  std::vector<LED> LED_STRIP_CONTAINER;

class LEDSTRIP: public LED_STRIP_CONTAINER
{

public:
    LEDSTRIP();
    LEDSTRIP(const char * confpath);
    void setBrightnessLED(int, int ) ; 
    void open(int, std::string);
    void setBrightness(int);

private:
    std::fstream confFile;

};




#endif 