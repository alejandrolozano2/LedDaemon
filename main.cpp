//#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include "leds.hpp"
#include "ledstrip.hpp"
#include <vector>

int main()
{
    std::cout << "hello from VS code" << std::endl;
    std::cout << "read leds.conf" << std::endl;

    LEDSTRIP myLEDS("leds.conf");


    int brightness;
    int i = 0 ;
    while(true)
    {
        
        std::cout << "set brigthness: " ;
        std::cin >> std::hex >> brightness;
        myLEDS.setBrightnessLED(i++,brightness);

        if(i >= myLEDS.size()) i = 0;

    }
    
    return 0;
}

