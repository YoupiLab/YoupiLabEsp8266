#ifndef LIBRARY_H
#define LIBRARY_H
#include <Wire.h> 
#include <ESP8266HTTPClient.h> 
//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <WiFiClient.h>

struct YoupiLabEsp8266{
    public:
      YoupiLabEsp8266(String APP_KEY, String APP_ID);

      int veriyAndConnectToWifi(const char* ssid, const char* password); //allows to connect to a wifi
      
      int Send_Data(int count, ...); //send data on our iot platform (https://iot.youpilab.com); return 1 in case of success and 0 in case of failure

      void executeAnAction(int nbr_args, ...); //execute an action return 1 in case of success and 0 in case of failure

      int executeTerminalTask(String TERMINAL_ID); // get info

      void getInformationOfThingCreated(); // You can have the information about your thing

      void countData();//count the number of data items sent to the object
      
      int executeAnActionWithTerminal(String TERMINAL_ID, String TASK_ID, String RESPONSE_OF_EXECUTION);//execute an action in the terminal

      int sendFeedback();//Send feedback after executing a task

      String getAppKey();
      String getBaseUrl();
      String getAppId();

      void setAppKey(String key);
      void setAppUrl(String url);
      void setAppID(String id);
   
    private:
      WiFiClientSecure client;
      String _APP_ID;
      String _APP_KEY;
      String _BASE_URL;
};



#endif
