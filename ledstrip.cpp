#include "ledstrip.hpp"

#if 0
LEDSTRIP::LEDSTRIP():RGB(3)
{

}

LEDSTRIP::LEDSTRIP(std::string r , std::string g, std::string b ):RGB(3)
{
    RGB[eRED].open(r);
    RGB[eGREEN].open(g);
    RGB[eBLUE].open(b);
}

void LEDSTRIP::setBrightnessLED(eLED_t led, int value ) 
{
    RGB[led].setBrightness(value);
}


/*Each Byte lane corresponds to */
void LEDSTRIP::setBrightness(int value )
{
    RGB[eBLUE].setBrightness(value & 0xff);
    RGB[eGREEN].setBrightness( (value >> 8) & 0xff );
    RGB[eRED].setBrightness( (value >> 16) & 0xff);
}

void LEDSTRIP::open(eLED_t led, std::string path)
{
    RGB[led].open(path);
}

#endif

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