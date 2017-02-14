//Includes
#include "Fsm.h"
#include "Webserver.h"
#include "Gpio.h"
#include "Timer.h"

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
  Fsm fsm(&webserver);

  while(1)
  {
    webserver.handleClient(); 
  }
}
