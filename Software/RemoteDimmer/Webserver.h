/*
 * Project: RemoteDimmer
 * File: Webserver.h
 * Date: 10.02.2017
 * Author: Kevin Fuerst
 */

#ifndef WEBSERVER_H_
#define WEBSERVER_H_

//Includes

//Forward declarations
class ESP8266WebServer;

typedef void (*cbFunction)(int, int*);

class Webserver
{
  public:
    Webserver(char* ssid, char* password);
    void handleClient(void);
    int registerCb(cbFunction f);
       
  private:
    enum {maxNumberOfArguments = 2};
    static ESP8266WebServer* server;
    static cbFunction client;
    static int data[maxNumberOfArguments];
    
    friend void getData();
    friend void ledOn();
    friend void ledOff(); 
  
};

#endif /* WEBSERVER_H_ */
