/*
 * 1 pour entier
 * 2 pour nombre à virgule
 * 3 pour string
 */
#include <YoupiLabEsp8266.h>



const char* ssid =  "Mon point d'acces";//
const char* password = "12344566789";//
int pho_res = A0;
String d;
String APP_ID     = "espc8123";  // Equipment APP ID
String APP_KEY    = "6033f31f";  // Equipment Key
YoupiLabEsp8266  esp(APP_ID, APP_KEY);
void setup() {
  Serial.begin(9600);
  //Connexion au Wi-Fi
  if (esp.veriyAndConnectToWifi(ssid, password) == 1) {
    Serial.println("Connexion reussi");
  }
 
  pinMode(pho_res, INPUT);
}

void loop() {

int lum=analogRead(A0);//lecture et recuperation du niveau de lumiere
float n1= 13.41;//nombre à virgule n1
float n2=3.14;//nombre à virgule n2
 d="YoupiLab";//string
 
  //pour envoyer des données sur la plateforme
  if (esp.Send_Data(4, 1, lum, 3, d, 2,n1, 2, n2) == 1) {
    Serial.println("Envoie reussi");
  }

Serial.println("countData");
esp.countData();//Compter le nombre de donnée dans l'equipement
delay(5000);


}
