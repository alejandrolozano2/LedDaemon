//#define _GLIBCXX_USE_CXX11_ABI 0


#include <iostream>
#include <vector>
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
    
    
    while(true)
    {
        pthread_mutex_lock(mData->mtx);
        mData->ptrAnimation->runAnimation(*mData->ptrMyLEDS);        
        pthread_mutex_unlock(mData->mtx);
        usleep(1000);
    }
    return NULL;
}

int main()
{


    mqd_t msq;
    struct mq_attr attr;
    /*Initialize the queue attributes*/
    char new_state_buffer[MAX_SIZE] = {0};
    char current_state_buffer[MAX_SIZE] = {0};
    ssize_t bytes_read;
    pshared_data_t mypThreadData;

    pthread_t th;
    pthread_mutex_t mxq; /* mutex used as quit flag */

    ANIMATION * animationhandler;
    ANIMATION * panimationhandler;

    std::cout << "LED Daemon Started" << std::endl;

    /*Create LED array from config file*/
    LEDSTRIP myLEDS("leds.conf");
    /*Create Annimation from animation files*/
    ANIMATION idleAnimation("idle.animation");
    ANIMATION startupAnimation("startup.animation");
    ANIMATION listeningAnimation("listening.animation"); 
    ANIMATION speakingAnimation("speaking.animation");
    ANIMATION thinkingAnimation("thinking.animation");

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /*Create the messages queues*/
    msq = mq_open( QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr  );
    pthread_mutex_init(&mxq,NULL);

    /*Begin Idle State*/
   // panimationhandler = &idleAnimation;
    startupAnimation.runAnimation(myLEDS);

    /*Init Data for pthread*/
    mypThreadData.mtx = &mxq;
    mypThreadData.ptrAnimation = &startupAnimation;
    mypThreadData.ptrMyLEDS = &myLEDS;

    /*Run Animation*/
    pthread_create(&th,NULL,runAnimation,&mypThreadData);
    
    std::cout << "Start Server: " << std::endl;
    while(true)
    {
        /*Receive Bytes from Message Queue*/
        bytes_read = mq_receive(msq, new_state_buffer, MAX_SIZE, NULL);

        /*If received message is different from previous*/ 
        if(strncmp(new_state_buffer, current_state_buffer, MAX_SIZE) != 0)
        {

            if (strncmp(new_state_buffer, "IDLE", 4) == 0) 
            {
                animationhandler = &idleAnimation;

            } else if (strncmp(new_state_buffer, "LISTENING", 9) == 0) {
                animationhandler = &listeningAnimation;

		    } else if (strncmp(new_state_buffer, "SPEAKING", 8) == 0) {
			    animationhandler = &speakingAnimation;

		    } else if (strncmp(new_state_buffer, "THINKING", 8) == 0) {
                animationhandler = &thinkingAnimation;

		    } else if (strncmp(new_state_buffer, "START", 5) == 0) {
                animationhandler = &startupAnimation;

		    }
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