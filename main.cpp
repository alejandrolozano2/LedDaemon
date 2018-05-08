
#include <iostream>
#include "leds.hpp"
#include "ledrgb.hpp"
#include <vector>
int main()
{
    std::cout << "hello from VS code" << std::endl;

    //vector or 3 LEDs
    std::vector<LED> myStripLED(2);
    
    LEDRGB myrgb(std::string("/sys/class/leds/pca995x:red1/brightness"), 
                std::string("/sys/class/leds/pca995x:green1/brightness"),
                std::string("/sys/class/leds/pca995x:blue1/brightness"));
   

    myStripLED[0].open("/sys/class/leds/pca995x:red0/brightness");
    myStripLED[1].open("/sys/class/leds/pca995x:green0/brightness");

    std::cout << "size of myStrip: " << myStripLED.size() << std::endl;
    myStripLED.push_back(LED("/sys/class/leds/pca995x:blue0/brightness"));    
    std::cout << "size of myStrip: " << myStripLED.size() << std::endl; 
    myStripLED[2].open("/sys/class/leds/pca995x:blue0/brightness");

    int brightness;
    while(true)
    {
        std::cout << "set brigthness: " ;
        std::cin >> std::hex >> brightness;

        myStripLED[0].setBrightness(brightness);
        myStripLED[1].setBrightness(brightness);
        myStripLED[2].setBrightness(brightness);

        myrgb.setBrightness( 0x7F007F);

    }
    
    return 0;
}

