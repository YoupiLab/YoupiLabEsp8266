  #include <YoupiLabEsp8266.h>
  
const char* ssid =  "Mon point d'acces";//
const char* password = "12344566789";//
  
  String APP_ID     = "dht41ffe";  // Equipment APP ID
  String APP_KEY    = "79a1a24f";  // Equipment Key
  YoupiLabEsp8266  esp(APP_ID, APP_KEY);
  int n = 2;
  int led1 = 4;
  int led2 = 5;
  int button1, button2;
  void setup() {
    Serial.begin(9600);
    if (esp.veriyAndConnectToWifi(ssid, password) == 1) {
      Serial.println("Connexion reussi");
    }
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
  }
  
  void loop() {
    esp.executeAnAction(n, &button1, &button2);
    Serial.print("button1=");
    Serial.println(button1);
    Serial.print("button2=");
    Serial.println(button2);
    if (button1 == 1) {
      digitalWrite(led1, HIGH);
    } else if (button1 == 0) {
      digitalWrite(led1, LOW);
    }
    if (button2 == 1) {
      digitalWrite(led2, HIGH);
    } else if (button2 == 0) {
      digitalWrite(led2, LOW);
    }
  
  }
