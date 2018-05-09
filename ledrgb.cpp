#include "ledrgb.hpp"

#if 0
LEDRGB::LEDRGB():RGB(3)
{

}

LEDRGB::LEDRGB(std::string r , std::string g, std::string b ):RGB(3)
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

void LEDRGB::open(eLED_t led, std::string path)
{
    RGB[led].open(path);
}

#endif

LEDRGB::LEDRGB():LED_STRIP_CONTAINER(3)
{

}

LEDRGB::LEDRGB(std::string r , std::string g, std::string b ):LED_STRIP_CONTAINER(3)
{
    iterator it = begin();
    it[0].open(r);
    it[1].open(g);
    it[2].open(b);
}

void LEDRGB::setBrightnessLED(eLED_t led, int value ) 
{
    iterator it = begin();
    it[led].setBrightness(value);
}


/*Each Byte lane corresponds to */
void LEDRGB::setBrightness(int value )
{
    iterator it = begin();
    it[eBLUE].setBrightness(value & 0xff);
    it[eGREEN].setBrightness( (value >> 8) & 0xff );
    it[eRED].setBrightness( (value >> 16) & 0xff);
}

void LEDRGB::open(eLED_t led, std::string path)
{
    iterator it = begin();
    it[led].open(path);
}