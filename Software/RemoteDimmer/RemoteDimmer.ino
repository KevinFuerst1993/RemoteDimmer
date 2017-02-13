//Includes
#include "Fsm.h"
#include "Webserver.h"
#include "Gpio.h"
#include "Timer.h"

//Global objects/variables
Fsm fsm;
int testVar = 0;

//Funcion prototyps
void webserverCb(int length, int* data);
void test(void *pArg);

enum{dimmMode = 0, onOffMode = 1, wakeUpMode = 2};

void setup() 
{
  //Test-----------------
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Program started");
  //--------------------
}


void loop() 
{
  Webserver webserver("FMBK-NG","Die21Tulpen");
  webserver.registerCb(webserverCb);

  //test
  Timer timer;
  timer.setInterval(1000);
  timer.setRepeatMode(true);
  timer.registerCb(test);
  timer.start(); 

  while(1)
  {
    webserver.handleClient(); 
    
  }
}

void webserverCb(int length, int* data)
{
  //test -------------
  for(int i = 0; i< length; ++i)
  {
    
    Serial.println("");
    Serial.print(data[i]);
  }
  //-----------------------
    
  switch(data[0])
  {
    case dimmMode:    fsm.setDimmLevel(data[1]);
                      fsm.process(evDimm);
                      break;

    case onOffMode:   if(data[1]) 
                      {
                        fsm.process(evOn);
                      }
                      else
                      {
                        fsm.process(evOff);
                      }
                      break;

    case wakeUpMode:  fsm.process(evWakeUp);
                      break;
    
  }
}

void test(void *pArg)
{
  static int count = 1;
  Serial.println("");
  Serial.print(count);
  count++;
  
  /*if(testVar == 0)
  {
    digitalWrite(LED_BUILTIN, LOW);
    testVar = 1;
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
    testVar = 0;
  }*/
}


