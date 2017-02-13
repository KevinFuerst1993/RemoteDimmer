//Includes
#include "Fsm.h"
#include "Webserver.h"
#include "ZeroDetectionGpio.h"

//Global objects/variables
Fsm fsm;

//Funcion prototyps
void webserverCb(int length, int* data);

enum{dimmMode = 0, onOffMode = 1, wakeUpMode = 2};

void setup() 
{
  //Test-----------------
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Program started");
  //--------------------
}
Webserver webserver("FMBK-NG","Die21Tulpen");
void loop() 
{
  webserver.registerCb(webserverCb);
  ZeroDetectionGpio gpio;
 
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




