/*
 * Project: RemoteDimmer
 * File: Fsm.h
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

#ifndef FSM_H_
#define FSM_H_

//Includes
#include "Timer.h"

//Forward declarations
class Gpio;
class Webserver;

class Fsm
{
  public:
    enum Event{evZeroDetection,evTimeout};
    Fsm(Webserver* webserver);
    void process(Event e); 
    
  private:
    void setDimmLevel(int dimmLvl);
    void dimmUp(void);
    void dimmDown(void);
    enum State{dimmState, onState, offState, wakeUpState};
    enum{dimmMode = 0, onOffMode = 1, upMode = 2, downMode = 3, wakeUpMode = 4};
    State currentState;
    int dimmLevel;
    int dimmFlag;
    int wakeUpCount;
    Gpio* zeroDetectionGpio;
    Gpio* outputGpio;
    static Webserver* webserver;
    static Fsm* fsm;
    Timer timer;
    static void zeroDetectionCb(void);
    static void timerInterruptCb(void *pArg);
    static void webserverCb(int length, int* data);
};

#endif /* FSM_H_ */
