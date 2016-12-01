#include <Firebase.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h> 
#include <Portal.h>
#include <SerialTransceiver.h>
#include <Transcriber.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <FirebaseArduino.h>
//sensor
#include "DHT.h"
#define DHTPIN D5// what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

const char* ssid     = "A";
const char* password = "12345678";
const int pinOutput0 = D0;
const int pinOutput1 = D1;
const int pinOutput2 = D2;
const int pinOutput3 = D3;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Temparatur
  dht.begin();
  Serial.println("DHTxx test!");

  //Reray
  pinMode(pinOutput0, OUTPUT);
  pinMode(pinOutput1, OUTPUT);
  pinMode(pinOutput2, OUTPUT);
  pinMode(pinOutput3, OUTPUT);
  //connect
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin("digital-project-60005.firebaseio.com", "ihQE3ZrnS0nOYPyOdc2hTBhCdcgO2z6fYtgTdxBf");

  Serial.println("Connect Firebase Successful");

}

void Autorun(float temp_S,int temp_F,int moisture_S,float moisture_F){
    
    if(moisture_S <= moisture_F){
          if(temp_S >= temp_F && temp_S <= temp_F){
            digitalWrite(pinOutput0, LOW);
            digitalWrite(pinOutput1, HIGH);
            digitalWrite(pinOutput2, HIGH);
            digitalWrite(pinOutput3, HIGH);
            Serial.print("___temp_S :");
            Serial.println(temp_S);
            Serial.print("___moisture_S :");
            Serial.println(moisture_S);
          }else  if(temp_S >= temp_F && temp_S <= temp_F+2){
            digitalWrite(pinOutput0, HIGH);
            digitalWrite(pinOutput1, LOW);
            digitalWrite(pinOutput2, HIGH);
            digitalWrite(pinOutput3, HIGH);
           Serial.print("___temp_S :");
        Serial.println(temp_S);
        Serial.print("___moisture_S :");
        Serial.println(moisture_S);
          }else  if(temp_S >= temp_F && temp_S <= temp_F+4){
            digitalWrite(pinOutput0, HIGH);
            digitalWrite(pinOutput1, HIGH);
            digitalWrite(pinOutput2, LOW);
            digitalWrite(pinOutput3, HIGH);
            Serial.print("___temp_S :");
        Serial.println(temp_S);
        Serial.print("___moisture_S :");
        Serial.println(moisture_S);
          }else  if(temp_S >= temp_F && temp_S <= temp_F+100){
            digitalWrite(pinOutput0, HIGH);
            digitalWrite(pinOutput1, HIGH);
            digitalWrite(pinOutput2, HIGH);
            digitalWrite(pinOutput3, LOW);
            Serial.print("___temp_S :");
        Serial.println(temp_S);
        Serial.print("___moisture_S :");
        Serial.println(moisture_S);;
          }else{
            digitalWrite(pinOutput0, HIGH);
            digitalWrite(pinOutput1, HIGH);
            digitalWrite(pinOutput2, HIGH);
            digitalWrite(pinOutput3, HIGH);
            Serial.print("___temp_S :");
            Serial.println(temp_S);
            Serial.print("___moisture_S :");
            Serial.println(moisture_S);
            }
    }else{
        digitalWrite(pinOutput0, HIGH);
        digitalWrite(pinOutput1, HIGH);
        digitalWrite(pinOutput2, HIGH);
        digitalWrite(pinOutput3, HIGH);
        Serial.print("___temp_S :");
        Serial.println(temp_S);
        Serial.print("___moisture_S :");
        Serial.println(moisture_S);
    }
}

void loop() {
  delay(1000);
  String rangeS = Firebase.getString("range");
  int moisture = Firebase.getInt("moisture");
  int temp = Firebase.getInt("temp");
  int range = rangeS.toInt();
  Serial.print("rang : ");
  Serial.println(range);
  Serial.print("moisture : ");
  Serial.println(moisture);
  Serial.print("temp : ");
  Serial.println(temp);


  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Firebase.setFloat("temp_Sensor", t);
  Firebase.setFloat("moisture_Sensor", f);
  
  if(range == 0){
    digitalWrite(pinOutput0, HIGH);
    digitalWrite(pinOutput1, HIGH);
    digitalWrite(pinOutput2, HIGH);
    digitalWrite(pinOutput3, HIGH);
  }else if(range >= 1 && range <= 15){
    // temparetur
    Autorun(t, temp, f, moisture);    
    // wewewe
  }else if(range >= 16  && range <= 24 ){
    digitalWrite(pinOutput0, LOW);
    digitalWrite(pinOutput1, HIGH);
    digitalWrite(pinOutput2, HIGH);
    digitalWrite(pinOutput3, HIGH);
  }else if (range >= 25 && range <= 50 ){
    digitalWrite(pinOutput0, HIGH);
    digitalWrite(pinOutput1, LOW);
    digitalWrite(pinOutput2, HIGH);
    digitalWrite(pinOutput3, HIGH);
  }else if (range >= 51 && range <= 75){
    digitalWrite(pinOutput0, HIGH);
    digitalWrite(pinOutput1, HIGH);
    digitalWrite(pinOutput2, LOW);
    digitalWrite(pinOutput3, HIGH);
  }else if(range >= 71 && range <= 100){
    digitalWrite(pinOutput0, HIGH);
    digitalWrite(pinOutput1, HIGH);
    digitalWrite(pinOutput2, HIGH);
    digitalWrite(pinOutput3, LOW);
  }else{
    Serial.println("Not value");
    }

    Serial.println("----------------------------------------------");
    Serial.println("");
    
}
