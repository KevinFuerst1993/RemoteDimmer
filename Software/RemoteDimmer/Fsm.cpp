/*
 * Project: RemoteDimmer
 * File: Fsm.cpp
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

//LightDimmer Includes
#include "Fsm.h"
#include "Gpio.h"
#include "Webserver.h"

Fsm* Fsm::fsm = 0;
Webserver* Fsm::webserver = 0;
Fsm::Fsm(Webserver* webserver)
  :dimmLevel(50), dimmFlag(0), currentState(offState), wakeUpCount(0)
{
  zeroDetectionGpio = new Gpio(Gpio::D5, Gpio::input);
  outputGpio = new Gpio(Gpio::D6, Gpio::output);
  zeroDetectionGpio->registerInterruptCb(zeroDetectionCb,Gpio::rising);

  timer.registerCb(timerInterruptCb);

  this->webserver = webserver;
  this->webserver->registerCb(webserverCb);

  fsm = this;
}

void Fsm::process(Event e)
{
  switch(currentState)
  {
    case dimmState:     if(e == evZeroDetection)
                        {
                          /*
                          Serial.println("Event ZeroDetection occured");
                          Serial.println("  Current State = dimmState");
                          Serial.print("  DimmLevel = ");
                          Serial.print(dimmLevel);
                          Serial.println("");
                          Serial.println("");
                          */
                          outputGpio->setOutput(Gpio::low);
                          timer.setInterval((100 - dimmLevel) / 10);
                         // timer.setInterval(5);
                          
                          timer.setRepeatMode(false);
                          timer.start();
                        }
                        else if(e == evTimeout)
                        {
                          /*
                          Serial.println("Event Timeout occured");
                          Serial.println("  Current State = dimmState");
                          Serial.print("  DimmLevel = ");
                          Serial.print(dimmLevel);
                          Serial.println("");
                          Serial.println("");
                          */
                          outputGpio->setOutput(Gpio::high);
                        }
                        break;
                                         
    case onState:       break;        
    
    case offState:      break;
    
    case wakeUpState:   if(e == evZeroDetection)
                        {
                          /*
                          Serial.println("Event ZeroDetection occured");
                          Serial.println("  Current State = wakeUpState");
                          Serial.print("  DimmLevel = ");
                          Serial.print(dimmLevel);
                          Serial.println("");
                          Serial.println("");
                          */
                          outputGpio->setOutput(Gpio::low);
                          timer.setInterval((100 - dimmLevel) / 10);
                          timer.setRepeatMode(false);
                          timer.start();
                        }
                        else if(e == evTimeout)
                        {
                          /*
                          Serial.println("Event Timeout occured");
                          Serial.println("  Current State = wakeUpState");
                          Serial.print("  DimmLevel = ");
                          Serial.print(dimmLevel);
                          Serial.println("");
                          Serial.println("");
                          */
                          outputGpio->setOutput(Gpio::high);
                          if(wakeUpCount == 50)
                          {
                            dimmLevel += 10;
                            wakeUpCount = 0;
                          }
                          ++wakeUpCount;

                          if(dimmLevel >= 100)
                          {
                            dimmLevel = 90;
                            currentState = onState; 
                          }
                        }
                        break;
  }
}

void Fsm::setDimmLevel(int dimmLvl)
{
  if((dimmLvl >= 0) && (dimmLvl <= 100))
  {
    dimmLevel = dimmLvl;
    if(dimmLevel % 10 >= 5)
    {
      dimmLevel += 10 - (dimmLevel % 10);
    }
    else
    {
      dimmLevel -= dimmLevel % 10;
    }
  }
}

void Fsm::dimmUp(void)
{
  Serial.println("DimmUp activated"); 
  Serial.print("  Old DimmLevel = ");
  Serial.print(dimmLevel);
  Serial.println("");
  if(currentState == offState)
  {
    dimmLevel = 10;
    fsm->currentState = dimmState;
    Serial.println("  Old state = offState");
    Serial.print("  New DimmLevel = ");
    Serial.print(dimmLevel);
    Serial.println("");
    Serial.println("  New State = dimmState");
    Serial.println("");
  }
  else if(currentState == onState)
  {
    fsm->currentState = offState;
    fsm->outputGpio->setOutput(Gpio::low);
    Serial.println("  Old state = onState");
    Serial.println("  New State = offState");
    Serial.println("");
  }
  else if(dimmLevel == 90 && currentState == dimmState)
  {
    fsm->currentState = onState;
    fsm->outputGpio->setOutput(Gpio::high);
    Serial.println("  Old state = dimmState");
    Serial.println("  New State = onState");
    Serial.println("");
  }
  else if(currentState == dimmState)
  {
    dimmLevel += 10;
    Serial.println("  Old state = dimmState");
    Serial.print("  New DimmLevel = ");
    Serial.print(dimmLevel);
    Serial.println("");
    Serial.println("  New State = dimmState");
    Serial.println("");
  }
}

void Fsm::dimmDown(void)
{
  Serial.println("DimmDown activated"); 
  Serial.print("  Old DimmLevel = ");
  Serial.print(dimmLevel);
  Serial.println("");
  
  if(currentState == onState)
  {
    dimmLevel = 90;
    fsm->currentState = dimmState;
    Serial.println("  Old state = onState");
    Serial.print("  New DimmLevel = ");
    Serial.print(dimmLevel);
    Serial.println("");
    Serial.println("  New State = dimmState");
    Serial.println("");     
  }
  else if(currentState == offState)
  {
    fsm->currentState = onState;
    fsm->outputGpio->setOutput(Gpio::high);
    Serial.println("  Old state = offState");
    Serial.println("  New State = onState");
    Serial.println("");
  }
  else if(dimmLevel == 10 && currentState == dimmState)
  {
    fsm->currentState = offState;
    fsm->outputGpio->setOutput(Gpio::low); 
    Serial.println("  Old state = dimmState");
    Serial.println("  New State = offState");
    Serial.println("");
  }
  else if(currentState == dimmState)
  {
    dimmLevel -= 10;
    Serial.println("  Old state = DimmState");
    Serial.print("  New DimmLevel = ");
    Serial.print(dimmLevel);
    Serial.println("");
    Serial.println("  New State = dimmState");
    Serial.println("");
  }
}

void Fsm::webserverCb(int length, int* data)
{
  switch(data[0])
  {
    case dimmMode:    if(data[1] >= 95)
                      {
                        Serial.println("Enter onState");
                        Serial.println("");
                        fsm->currentState = onState;
                        fsm->outputGpio->setOutput(Gpio::high);
                      }
                      else if(data[1] <= 5)
                      {
                        Serial.println("Enter offState");
                        Serial.println("");
                        fsm->currentState = offState;
                        fsm->outputGpio->setOutput(Gpio::low);
                      }
                      else
                      {
                        fsm->setDimmLevel(data[1]);
                        fsm->currentState = dimmState;
                        fsm->outputGpio->setOutput(Gpio::low);
                        Serial.print("Enter dimmState. DimmLevel = ");
                        Serial.print(fsm->dimmLevel);
                        Serial.println("");
                        Serial.println("");
                      }
                      break;

    case onOffMode:   if(data[1]) 
                      {
                        Serial.println("Enter onState");
                        Serial.println("");
                        fsm->currentState = onState;
                        fsm->outputGpio->setOutput(Gpio::high);
                      }
                      else
                      {
                        Serial.println("Enter offState");
                        Serial.println("");
                        fsm->currentState = offState;
                        fsm->outputGpio->setOutput(Gpio::low);
                      }
                      break;
    
    case upMode:      fsm->dimmUp();
                      break;

    case downMode:    fsm->dimmDown();
                      break;

    case wakeUpMode:  Serial.println("Enter wakeUpState");
                      Serial.println("");
                      fsm->setDimmLevel(10);
                      fsm->currentState = wakeUpState;
                      fsm->outputGpio->setOutput(Gpio::low);
                      break;
  }
}

void Fsm::zeroDetectionCb(void)
{
  fsm->process(evZeroDetection);
}

void Fsm::timerInterruptCb(void *pArg)
{
  fsm->process(evTimeout);
}

