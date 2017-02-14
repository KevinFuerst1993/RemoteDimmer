/*
 * Project: RemoteDimmer
 * File: Timer.cpp
 * Date: 13.02.2017
 * Author: Kevin Fuerst
 */
#include "Timer.h"

void dummyFunction(void *pArg);

Timer::Timer()
  :interval(0),modeFlag(0),f(0)
{
  os_timer_setfn(&timer, dummyFunction, NULL); //set dummyFunction as default callback function
}

void Timer::setInterval(int interval)
{
  this->interval = interval;
}

void Timer::setRepeatMode(bool modeFlag)
{
  this->modeFlag = modeFlag;
}

void Timer::start(void)
{
  /*if(f != 0)
  {
    os_timer_setfn(&timer, f, NULL);
  }*/
  
  if(interval != 0 && f != 0)
  {
    os_timer_arm(&timer, interval, modeFlag);
  }
}
/*
void Timer::stop(void)
{
  //os_timer_setfn(&timer, f, NULL);
  os_timer_arm(&timer, interval, false);
}*/

void Timer::registerCb(timeoutCb f)
{
  this->f = f;
  os_timer_setfn(&timer, f, NULL);
}

void dummyFunction(void *pArg)
{
}

