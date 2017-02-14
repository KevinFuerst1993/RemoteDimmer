/*
 * Project: RemoteDimmer
 * File: Webserver.cpp
 * Date: 10.02.2017
 * Author: Kevin Fuerst
 */

//LightDimmer Includes
#include "Webserver.h"

//Arduino Includes
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//Friend Functions
void ledOn(void);
void ledOff(void);
void getData(void);

ESP8266WebServer* Webserver::server = 0;
int Webserver::data[maxNumberOfArguments] = {0};
cbFunction Webserver::client = 0;

Webserver::Webserver(char* ssid, char* password)
{
  server = new ESP8266WebServer(80);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  WiFi.begin(ssid, password);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); 
  }
  
  MDNS.begin("esp8266");

  server->on("/",getData); //Call through: "ip"/?mode=1&arg=2
  //test------------------------
  server->on("/ledOn",ledOn);
  server->on("/ledOff",ledOff);
  //--------------------------

  server->begin(); 
}

int Webserver::registerCb(cbFunction f)
{
  if(client != 0)
  {
    return 1;
  }
  else
  {
    client = f;
    return 0;
  }
}

void Webserver::handleClient(void)
{
  Webserver::server->handleClient();
}

void getData(void)
{
  int argumentCount;
  String message;
  
  argumentCount = Webserver::server->args();

  if(argumentCount > Webserver::maxNumberOfArguments)
    argumentCount = Webserver::maxNumberOfArguments;
  
  for (int i=0; i<argumentCount; i++)
  {
    message = Webserver::server->arg(i);
    Webserver::data[i] = message.toInt();  
  }

  Webserver::server->send(200, "text/plain", "Request done");
  
  if(Webserver::client != 0)
    Webserver::client(argumentCount, Webserver::data);

}

void ledOn(void)
{
  digitalWrite(LED_BUILTIN, LOW);
  Webserver::server->send(200, "text/plain", "Led On");
}

void ledOff(void)
{
  digitalWrite(LED_BUILTIN, HIGH);
  Webserver::server->send(200, "text/plain", "Led Off");
}

