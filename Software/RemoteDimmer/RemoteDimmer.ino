//Includes
#include "Fsm.h"
#include "Webserver.h"
#include "Gpio.h"
#include "Timer.h"
/*
void test(void *pArg);
int testArg = 0;
 Gpio gpio(Gpio::D6, Gpio::output);
*/
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
  //Webserver webserver("FMBK-NG","Die21Tulpen");
  Webserver webserver("MySpot","123456789");
  Fsm fsm(&webserver);
/*
  Timer timer;
  timer.setInterval(3);
  timer.registerCb(test);
  timer.setRepeatMode(true);
  timer.start();
  */
 
  
  while(1)
  {
    webserver.handleClient(); 
  }
}

/*
void test(void *pArg)
{
  if(testArg == 0)
  {
    testArg = 1;
    gpio.setOutput(Gpio::high);
  }
  else
  {
    testArg = 0;
    gpio.setOutput(Gpio::low);
  }
}
*/
