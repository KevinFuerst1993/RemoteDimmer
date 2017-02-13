/*
 * Project: RemoteDimmer
 * File: Timer.h
 * Date: 13.02.2017
 * Author: Kevin Fuerst
 */

#ifndef TIMER_H_
#define TIMER_H_

//Includes
//#include <ESP8266mDNS.h>
extern "C" 
{
  #include "user_interface.h"
}

//Forward declarations

typedef void (*timeoutCb)(void *pArg);

class Timer
{
  public:
    Timer();
    void setInterval(int interval);
    void setRepeatMode(bool modeFlag);
    void start(void);
    //void stop(void); This Function doesnt work
    void registerCb(timeoutCb f);
    
  private:
    int interval;
    bool modeFlag;
    timeoutCb f;
    os_timer_t timer;
    //static void dummyFunction(void *pArg);

};



#endif /* TIMER_H_ */
