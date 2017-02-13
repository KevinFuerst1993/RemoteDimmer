/*
 * Project: RemoteDimmer
 * File: Fsm.h
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

#ifndef FSM_H_
#define FSM_H_

//Includes

//Forward declarations
class Gpio;

enum Event{evOn,evOff,evDimm,evWakeUp};

class Fsm
{
  public:
    Fsm();
    void process(Event e); 
    void setDimmLevel(int dimmLevel);
    
  private:
    enum State{dimmState, onState, offState, wakeUpState};
    State currentState;
    int dimmLevel;
    Gpio* zeroDetectionGpio;
    Gpio* outputGpio;
    static void interruptCb(void);
};

#endif /* FSM_H_ */
