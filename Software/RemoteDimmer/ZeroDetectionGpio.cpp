/*
 * Project: RemoteDimmer
 * File: ZeroDetectionGpio.cpp
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

//LightDimmer Includes
#include "ZeroDetectionGpio.h"

//Arduino Includes
#include <ESP8266mDNS.h>

ZeroDetectionGpio::ZeroDetectionGpio()
{
  pinMode(D0,INPUT);
  //attachInterrupt(digitalPinToInterrupt(16), ISR, CHANGE);
  attachInterrupt(D0, interruptHandler, RISING);
}

void ZeroDetectionGpio::interruptHandler(void)
{
  //test application
  Serial.println("Interrupt occured");
}

