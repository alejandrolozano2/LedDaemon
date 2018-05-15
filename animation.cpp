#include "animation.hpp"
#include <string>
#include <sstream>
#include <unistd.h>

ANIMATION::ANIMATION()
{}

ANIMATION::ANIMATION(const char * filepath)
{
    std::string tempstr;
    animationFile.open(filepath);
    
    int linenumber = 0;
    while(getline(animationFile,tempstr))
    {       
        fill_ledvalues(tempstr,linenumber);
        linenumber++;
    }

}

void ANIMATION::fill_ledvalues(std::string & linestr, int line)
{
    
    std::stringstream stream(linestr);
    int tempval;
    strip_state_t lstrip_sate;

    /*First element is time*/
    stream >> lstrip_sate.time_ms;

    /*Next Elements are colors*/
    while(stream)
    {
        stream >> tempval;
        lstrip_sate.ledvalues.push_back(tempval);
    }
     
    /*Add element of state values*/
    strip_state.push_back(lstrip_sate);
   
}

int ANIMATION::getSizeStates()
{
    return strip_state.size();
}

void ANIMATION::setState(LEDSTRIP & myLEDs, int state)
{
    int  brightvalue;
    /*Loop for each LED*/
    for(brightvalue = 0 ; brightvalue < myLEDs.size(); brightvalue++)
    {
        myLEDs.setBrightnessLED(brightvalue, strip_state[state].ledvalues[brightvalue]);
    }


}

int ANIMATION::getTime(int state)
{
    return strip_state[state].time_ms;
}

/*One shot Animation*/
void ANIMATION::runAnimation(LEDSTRIP & myLEDs)
{
    int state, brightvalue;

    /*loop for each state*/
    for(state = 0; state < strip_state.size() ; state++)
    {

        setState(myLEDs,state);
        usleep(strip_state[state].time_ms * 1000 );
    }
} 