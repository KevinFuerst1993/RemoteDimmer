/*
 * Project: RemoteDimmer
 * File: Fsm.cpp
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

//LightDimmer Includes
#include "Fsm.h"

//Arduino Includes

Fsm::Fsm()
  :currentState(offState), dimmLevel(0)
{
  
}


void Fsm::process(Event e)
{
  switch(currentState)
  {
    case dimmState:     if(e == evDimm)
                        {
                          
                        }
                        else if(e == evOn)
                        {
                          currentState
                        }
                     
      
    case onState:
    
    case offState:
    
    case wakeUpState:
  }
  
}

void Fsm::setDimmLevel(int dimmLevel)
{
  this->dimmLevel = dimmLevel;
}

