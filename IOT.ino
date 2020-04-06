#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "https://iot1-c13c7.firebaseio.com"
#define FIREBASE_AUTH "wrRl3OwKogTjnkVWdqjV4zqytImKpic13kKIuqHC"
#define WIFI_SSID "IOT_NETWORK"
#define WIFI_PASSWORD "12345678"
const double VCC = 3.3;            
const double R2 = 10000;            
const double adc_resolution = 1023; 
const double A = 0.001129148; 
const double B = 0.000234125;
const double C = 0.0000000876741; 
String gelen;
#define role 14//d5
FirebaseData Data;

void setup() {
    Serial.begin(9600);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
   Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  pinMode(role,OUTPUT);
  digitalWrite(role,LOW);

}

void loop() {
  double Vout, Rth, temperature, adc_value; 

  adc_value = analogRead(A0);
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;
  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));  //kelvin 
  temperature = temperature - 273.15;//c 
  Serial.println(temperature);
  delay(250);
  Firebase.setDouble(Data,"deger",temperature);
  delay(50);
  Firebase.getString(Data,"kontrol",gelen);
  delay(50);
  if(gelen=="0"){
    digitalWrite(role,LOW);
    delay(50);
     Serial.println("kapalı");
  }
  else if(gelen=="1"){
  digitalWrite(role,HIGH);
  delay(50);
   Serial.println("acik");}
   delay(250);
   
}
