/*
 * Project: RemoteDimmer
 * File: Gpio.h
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 * Note: Not every GPIO seems to generate interrupts. D0 hasent worked. D5 and D6 seem to work.
 */

#ifndef GPIO_H_
#define GPIO_H_

//Includes
#include <ESP8266mDNS.h>

//Forward declarations

typedef void (*interruptCb)(void);

class Gpio
{
  public:
    enum Pin{D0 = 16, D1 = 5, D2 = 4, D3 = 0, D4 = 2, D5 = 14, D6 = 12, D7 = 13, D8 = 15};
    enum Dir{input = INPUT, output = OUTPUT};
    enum Level{low = LOW, high = HIGH};
    enum InterruptMode{change = CHANGE, rising = RISING, falling = FALLING};
    
    Gpio(Pin pin, Dir dir);
    void setOutput(Level level);
    int registerInterruptCb(interruptCb f, InterruptMode intMode);
    
  private:
    Pin pin;
    Dir dir;
};



#endif /* GPIO_H_ */
