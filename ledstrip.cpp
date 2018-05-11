#include "ledstrip.hpp"

LEDSTRIP::LEDSTRIP()
{

}

LEDSTRIP::LEDSTRIP(const char * confpath)
{
    confFile.open(confpath);
    std::string mstring;
    
    while (getline(confFile,mstring))
    {
        push_back(LED(mstring)); 
    }
}

void LEDSTRIP::setBrightnessLED(int led, int value ) 
{
    iterator it = begin();
    it[led].setBrightness(value);
}


void LEDSTRIP::setBrightness(int value )
{
    for(iterator it = begin(); it != end(); it++)
    it->setBrightness(value);

}

void LEDSTRIP::open(int led, std::string path)
{
    iterator it = begin();
    it[led].open(path);
}