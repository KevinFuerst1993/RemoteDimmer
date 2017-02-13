/*
 * Project: RemoteDimmer
 * File: ZeroDetectionGpio.h
 * Date: 12.02.2017
 * Author: Kevin Fuerst
 */

#ifndef ZERODETECTIONGPIO_H_
#define ZERODETECTIONGPIO_H_

//Includes

//Forward declarations

class ZeroDetectionGpio
{
  public:
    ZeroDetectionGpio();
    
  private:
    enum{D0 = 16};
    static void interruptHandler(void);
  
};



#endif /* ZERODETECTIONGPIO_H_ */
