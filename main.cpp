#include <iostream>
#include <vector>
#include <map>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "leds.hpp"
#include "ledstrip.hpp"
#include "animation.hpp"

#include "common.h"


typedef struct 
{
    ANIMATION * ptrAnimation;
    LEDSTRIP * ptrMyLEDS;
    pthread_mutex_t * mtx;
}pshared_data_t;
 
void *runAnimation(void *arg)
{
    pshared_data_t * mData  = (pshared_data_t *)arg;
    ANIMATION * lptrAnimation = mData->ptrAnimation;

    int time;  
    while(true)
    {

        for(int state = 0; state < mData->ptrAnimation->getSizeStates() ; state++)
        {
            pthread_mutex_lock(mData->mtx);
            mData->ptrAnimation->setState(*mData->ptrMyLEDS,state);
            time = mData->ptrAnimation->getTime(state)* 1000;
            pthread_mutex_unlock(mData->mtx);
            usleep(time);

            if(lptrAnimation != mData->ptrAnimation) 
            {
                lptrAnimation = mData->ptrAnimation;
                break;
            }
        }

    }
    return NULL;
}

int main()
{


    mqd_t msq;
    struct mq_attr attr;
    char new_state_buffer[MAX_SIZE] = {0};
    char current_state_buffer[MAX_SIZE] = {0};
    ssize_t bytes_read;
    pshared_data_t mypThreadData;
    pthread_t th;
    pthread_mutex_t mxq;
    ANIMATION * animationhandler;

    std::cout << "LED Daemon Started" << std::endl;

    /*Create LED array from config file*/
    LEDSTRIP myLEDS("leds.conf");

    /*Create Annimation from animation files*/
    typedef  std::map<std::string, ANIMATION * > listAnimation_t;
    listAnimation_t listAnimation;
    
    std::fstream AnimationFile;
    AnimationFile.open("Animations.conf");
    std::string  lastanimationfile, animationfiles;

    while(getline(AnimationFile,animationfiles))
    {
        listAnimation.insert(listAnimation_t::value_type(animationfiles , new ANIMATION(animationfiles.c_str())));
        lastanimationfile = animationfiles;
    }

    /*Attributes of Message Queues*/
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /*Create the messages queues*/
    msq = mq_open( QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr  );
    pthread_mutex_init(&mxq,NULL);

    /*Init Data for pthread*/
    mypThreadData.mtx = &mxq;
    /*Begin Idle State*/;
    mypThreadData.ptrAnimation = listAnimation[lastanimationfile];
    mypThreadData.ptrMyLEDS = &myLEDS;

    /*Run Animation*/
    pthread_create(&th,NULL,runAnimation,&mypThreadData);
    
    std::string mystring; 
    std::cout << "Start Server " << std::endl;

    while(true)
    {
        /*Receive Bytes from Message Queue*/        
        bytes_read = mq_receive(msq, new_state_buffer, MAX_SIZE, NULL);

        /*If received message is different from previous*/ 
        if(strncmp(new_state_buffer, current_state_buffer, MAX_SIZE) != 0)
        {
            /*Get animation*/
            mystring = new_state_buffer;                       
            animationhandler = listAnimation[new_state_buffer];

            strcpy(current_state_buffer,new_state_buffer);

            pthread_mutex_lock(&mxq);
             mypThreadData.ptrAnimation = animationhandler;
            pthread_mutex_unlock(&mxq);
        }
    }
        
        mq_close(msq); 
        mq_unlink(QUEUE_NAME);
    
    return 0;
}