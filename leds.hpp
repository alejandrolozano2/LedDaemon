#ifndef LEDS_H
#define LEDS_H

#include <iostream>
#include<fstream>



class LED
{

public:
    void open();
    void open(std::string path);
    void close();
    void setBrightness(int);
    int getBrightness();

    LED(std::string path = "");

private:
    std::string led_path;
    std::fstream fs_brightness;
};



#endif