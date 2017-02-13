/*
 * Project: RemoteDimmer
 * File: Fsm.cpp
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

//LightDimmer Includes
#include "Fsm.h"
#include "Gpio.h"

//Arduino Includes

Fsm::Fsm()
  :currentState(offState), dimmLevel(0)
{
  zeroDetectionGpio = new Gpio(Gpio::D0, Gpio::input);
  outputGpio = new Gpio(Gpio::D1, Gpio::output);

  zeroDetectionGpio->registerInterruptCb(interruptCb,Gpio::rising);
  
}


void Fsm::process(Event e)
{
  switch(currentState)
  {
    case dimmState:     if(e == evOn)
                        {
                          currentState == onState;
                        }
                        else if(e == evOff)
                        {
                          currentState == offState;
                        }
                        else if(e == evWakeUp)
                        {
                          currentState == wakeUpState;
                        }
                        break;
                                         
    case onState:       if(e == evDimm)
                        {
                          currentState == dimmState;  
                        }
                        else if(e == evOff)
                        {
                          currentState == offState;
                        }
                        else if(e == evWakeUp)
                        {
                          currentState == wakeUpState;
                        }
                        break;        
    
    case offState:      if(e == evDimm)
                        {
                          currentState == dimmState; 
                        }
                        else if(e == evOn)
                        {
                          currentState == onState;
                        }
                        else if(e == evWakeUp)
                        {
                          currentState == wakeUpState;
                        }
                        break;
    
    case wakeUpState:   if(e == evDimm)
                        {
                          currentState == dimmState; 
                        }
                        else if(e == evOn)
                        {
                          currentState == onState;
                        }
                        else if(e == evOff)
                        {
                          currentState == offState;
                        }
                        break;
  }
}

void Fsm::setDimmLevel(int dimmLevel)
{
  this->dimmLevel = dimmLevel;
}

void Fsm::interruptCb(void)
{
  
}

