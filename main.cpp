
#include <iostream>
#include "leds.hpp"
#include <vector>
int main()
{
    std::cout << "hello from VS code" << std::endl;
    

    LED LedR1;
    LED LedB1;
    std::vector<LED> myStripLED(4);
    std::vector<LED>::iterator itLED;;


   itLED = myStripLED.end();

    myStripLED[0].open("/sys/class/leds/pca995x:red0/brightness");
    myStripLED[1].open("/sys/class/leds/pca995x:red1/brightness");
    myStripLED[2].open("/sys/class/leds/pca995x:red2/brightness");
    myStripLED[3].open("/sys/class/leds/pca995x:red3/brightness");

    std::cout << "size of myStrip: " << myStripLED.size() << std::endl;

    itLED = myStripLED.insert(itLED, LED("/sys/class/leds/pca995x:green3/brightness"));
    myStripLED[4].open("/sys/class/leds/pca995x:green3/brightness");

    std::cout << "size of myStrip: " << myStripLED.size() << std::endl; 
    int brightness;
    while(true)
    {
        std::cout << "set LedR1 brigthness: " ;
        std::cin >> brightness;

        myStripLED[0].setBrightness(brightness);
        myStripLED[1].setBrightness(brightness);
        myStripLED[2].setBrightness(brightness);
        myStripLED[3].setBrightness(brightness);
        myStripLED[4].setBrightness(brightness);
      //  LedR1.setBrightness(brightness);
      //  LedB1.setBrightness(brightness);
        
      //  std::cout << " myStripLED[2] brigthness set to: " << myStripLED[2].getBrightness() << std::endl ;

    }
    
    return 0;
}

