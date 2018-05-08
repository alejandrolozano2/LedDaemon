#include "ledrgb.hpp"

LEDRGB::LEDRGB()
{

}

LEDRGB::LEDRGB(std::string r , std::string g, std::string b )
{
    RGB[eRED].open(r);
    RGB[eGREEN].open(g);
    RGB[eBLUE].open(b);
}

void LEDRGB::setBrightnessLED(eLED_t led, int value ) 
{
    RGB[led].setBrightness(value);
}


/*Each Byte lane corresponds to */
void LEDRGB::setBrightness(int value )
{
    RGB[eBLUE].setBrightness(value & 0xff);
    RGB[eGREEN].setBrightness( (value >> 8) & 0xff );
    RGB[eRED].setBrightness( (value >> 16) & 0xff);
}