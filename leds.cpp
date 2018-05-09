#include "leds.hpp"


LED::LED(std::string path):led_path(path)
{
  open();
}

void LED::open()
{
    if(!led_path.empty())
    {
        fs_brightness.open(led_path);
       
    }
}

void LED::open(std::string path)
{
    led_path = path;
    open();
}

void LED::close()
{
    fs_brightness.close();
}

void LED::setBrightness(int value)
{

    fs_brightness << value;
    fs_brightness.clear();
    fs_brightness.seekg(0, fs_brightness.beg);

};

int LED::getBrightness()
{
    int value;

    fs_brightness.clear();
    fs_brightness.seekg(0, fs_brightness.beg);
    fs_brightness >> value;

    return value;

}