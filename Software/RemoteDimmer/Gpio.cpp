/*
 * Project: RemoteDimmer
 * File: ZeroDetectionGpio.cpp
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

//LightDimmer Includes
#include "Gpio.h"

//Arduino Includes


Gpio::Gpio(Pin pin, Dir dir)
  :pin(pin),dir(dir)
{
  pinMode(pin,dir);
}

void Gpio::setOutput(Level level)
{
  if(dir == output)
  {
    digitalWrite(pin, level);
  }
}

int Gpio::registerInterruptCb(interruptCb f, InterruptMode intMode)
{
  attachInterrupt(pin, f, intMode);
  //attachInterrupt(digitalPinToInterrupt(16), ISR, CHANGE);
}


