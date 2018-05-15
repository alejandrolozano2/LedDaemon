#ifndef ANIMATION_H
#define ANIMATION_H

#include "ledstrip.hpp"



class ANIMATION
{

private:

typedef struct
{
    int time_ms;
    std::vector<int> ledvalues;
}strip_state_t;

    std::fstream animationFile;
    std::vector<strip_state_t> strip_state;
    
    void fill_ledvalues(std::string & , int);
    
public:
    ANIMATION();
    ANIMATION(const char *);
    int getSizeStates();
    void runAnimation(LEDSTRIP &);
    void setState(LEDSTRIP &, int);
    int getTime(int state);
};



#endif