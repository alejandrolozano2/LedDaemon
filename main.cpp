//#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include "leds.hpp"
#include "ledrgb.hpp"
#include <vector>

int main()
{
    std::cout << "hello from VS code" << std::endl;
    std::cout << "read leds.conf" << std::endl;

    std::ifstream ledsconf("leds.conf");
    std::string mstring;

    std::vector<LEDRGB> myrgb(4);
    int i = 0;

    while (getline(ledsconf,mstring))
    {
        std::cout << mstring << std::endl;
        myrgb[i/3].open((LEDRGB::eLED_t)(i%3),mstring);         
        i++;
    }

    int brightness;
    while(true)
    {
        std::cout << "set brigthness: " ;
        std::cin >> std::hex >> brightness;

        myrgb[0].setBrightness( 0x3F0000 + brightness);
        myrgb[1].setBrightness( 0x003F00 - brightness);
        myrgb[2].setBrightness( 0x00003F * brightness);
        myrgb[3].setBrightness( 0x3F003F & brightness);

    }
    
    return 0;
}

