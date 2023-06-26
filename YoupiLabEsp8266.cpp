#include "YoupiLabEsp8266.h"
WiFiClient wifi;

HTTPClient httpClient;

YoupiLabEsp8266::YoupiLabEsp8266(String APP_ID, String APP_KEY): _APP_ID(APP_ID), _APP_KEY(APP_KEY), _BASE_URL("https://iot.youpilab.com/api"){}

/********************************************** Les SETTER ET GETTER */
/*
  get app key
*/
String YoupiLabEsp8266::getAppKey(){
  return _APP_KEY;
}
/*
  get app id
*/
String YoupiLabEsp8266::getAppId(){
  return _APP_ID;
}
/*
  get set app key
*/
void YoupiLabEsp8266::setAppKey(String appkey){
       _APP_KEY = appkey;
}
/*
  get app id
*/
void YoupiLabEsp8266::setAppID(String appid){
      _APP_ID = appid;
}
/*
  get base url
*/
String YoupiLabEsp8266::getBaseUrl(){
     return _BASE_URL;
}

/*
  allows to connect to a wifi
*/
int YoupiLabEsp8266::veriyAndConnectToWifi(const char* ssid, const char* password){
  delay(200); 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  
   return 1;
}
/*
  Execute an action
*/
void YoupiLabEsp8266::executeAnAction(int nbr_args, ...){
  /***********retrieving instructions to be executed from the IoT platform ******/
    String post_url = _BASE_URL + "/controls/get?" + "APP_ID=" + _APP_ID + "&APP_KEY=" + _APP_KEY;
    
    client.setInsecure();
    httpClient.begin(client,post_url); 
    int httpCode=httpClient.GET();
       if (httpCode==HTTP_CODE_OK){
    String etatb=httpClient.getString();
      etatb.replace("\n", "");//processing the recovered string
      etatb.replace("[", "");
      etatb.replace("]", "");
      etatb.replace(",", "");
      etatb.replace(" ", "");
      etatb.trim();
      if (etatb !=""){
      va_list liste_arguments;
      va_start(liste_arguments, nbr_args);
      int a=0;
      for (int i = 0; i < nbr_args; i++) {
        int* val_ptr = va_arg(liste_arguments, int*);
        char etat= etatb.charAt(a);
        *val_ptr = etat - '0';  // store the character value in the pointer to the corresponding variable
        a++;
     }

     va_end(liste_arguments);
   } 
 } 
}

/*
  send  data on our iot platform (https://iot.youpilab.com); return 1 in case of success and 0 in case of failure
*/
 int YoupiLabEsp8266::Send_Data(int count, ...){
      client.setInsecure();

 va_list args;//Declare variable argument list
  va_start(args, count);//Initializes variable argument list with last known parameter
  String post_url = _BASE_URL + "/data/send?" + "APP_ID=" + _APP_ID + "&APP_KEY=" + _APP_KEY;//Builds GET request URL with identification parameters
    int posi= 1;
  for (int i = 0; i < count; ++i) {

    int argType = va_arg(args, int);
    if (argType == 1) { // The argument is an integer
      int val = va_arg(args, int);
      post_url += "&P" +String (posi) + "=" + val;
    } else if (argType == 2) { // The argument is an double
      double val = va_arg(args, double);
      post_url += "&P" +String (posi) + "=" + val;
    } else if (argType == 3) { // The argument is an string
      String val = va_arg(args, String);
      post_url += "&P" + String (posi) + "=" + val;
    } else {
      // The type of argument is unknown
      Serial.print("le type d'argument est inconnue");
    }
    posi++;//Increments parameter position
  }
  va_end(args);//Terminates use of variable arguments
      httpClient.begin(client,post_url); //Starts an HTTP GET request with the constructed URL
      int httpResponseCode = httpClient.GET();//Sends request and retrieves HTTP response code
      if (httpResponseCode > 0) {
       String payload = httpClient.getString();//Retrieves server response
        return 1;
      }
      else {
        String payload = httpClient.getString();//Retrieves server response
        return 0;
      }
      delay(1000);
}

/*
  Get information from the created Thing
*/
void YoupiLabEsp8266::getInformationOfThingCreated(){
     client.setInsecure();

      String post_url = "https://iot.youpilab.com/api/data/send?APP_ID=";

      post_url+=_APP_ID; //id of thing
      post_url +="&APP_KEY=";
      post_url +=_APP_KEY; // key of thing
    
      /*Send reqette*/
      httpClient.begin (client,post_url); 
      int httpResponseCode = httpClient.GET();
      if (httpResponseCode > 0) {
        
       String payload = httpClient.getString();//Retrieves server response

        Serial.println(payload);
      }
      else {
          Serial.println(httpResponseCode);
      }
      delay(1000);

}
/*
  You can execute a task you have written in the terminal thing using this methode 
*/
int YoupiLabEsp8266::executeTerminalTask(String TERMINAL_ID){
  client.setInsecure();

  String post_url = "https://iot.youpilab.com/api/terminal/?TERM=";
  post_url+=TERMINAL_ID;
  httpClient.begin (client,post_url); 
  int httpResponseCode = httpClient.GET();
  if (httpResponseCode > 0) {
    
    String payload = httpClient.getString();//Retrieves server response

    return 1;
  }
  else {
     return 0;
  }
  delay(1000);
}
/*
  count the number of data received by our iot platform
*/
void YoupiLabEsp8266::countData(){
    client.setInsecure();

    String post_url = "https://iot.youpilab.com/api/data/count?APP_ID=";

    post_url+=_APP_ID;
    post_url +="&APP_KEY=";
    post_url +=_APP_KEY;

    httpClient.begin (client,post_url); 
    int httpResponseCode = httpClient.GET();
    if (httpResponseCode > 0) {
      String payload = httpClient.getString();//Retrieves server response
      Serial.println(payload);
    }
    else {
      
      Serial.println(httpResponseCode);
      
    }
    delay(1000);
}

/*
  These informations must be used to execute the following request which will display the response in terminal of thing
*/
int YoupiLabEsp8266::executeAnActionWithTerminal(String TERMINAL_ID, String TASK_ID, String RESPONSE_OF_EXECUTION){
    client.setInsecure();

    String post_url = "https://iot.youpilab.com/api/terminal/response/?TERM=";
    post_url+=TERMINAL_ID;
    post_url +="&TASK_ID=";
    post_url +=TASK_ID;
    post_url +="&RESP=";
    post_url +=RESPONSE_OF_EXECUTION;
      
    httpClient.begin (client,post_url); 
    int httpResponseCode = httpClient.GET();
    if (httpResponseCode > 0) {
      String payload = httpClient.getString();//Retrieves server response
     return 1;
    }
    else {
      
      return 0;
      
    }
}

/*
  send feed back
*/
int YoupiLabEsp8266::sendFeedback() {
    client.setInsecure();

    String post_url = "https://iot.youpilab.com/api/controls/executed?APP_ID=";
    post_url += _APP_ID;
    post_url += "&APP_KEY=";
    post_url += _APP_KEY;

    httpClient.begin(client, post_url);
    int httpResponseCode = httpClient.GET();
    if (httpResponseCode > 0) {
        String payload = httpClient.getString();//Retrieves server response
        if (payload != "") {
            payload = "";
            return 1;
        } else {
            return 0;
        }
    }

    return -1; 
}

