#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "https://smarthomeiot-9dee0.firebaseio.com/"
#define FIREBASE_AUTH "JMv4WhTmrGGthjIGGM0ktrSOEi0KOoVTES2snxc4"
#define WIFI_SSID "Lia"
#define WIFI_PASSWORD "chabona0412"

#define flame 2     //D4
#define buzzer 14   //D5
#define ldr 12      //D6
#define led 13      //D7

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData firebaseData;

String path = "/Node1";

int valFlame = HIGH; //tidak ada api
int valLdr = LOW;

void setup()
{

  Serial.begin(115200);

  pinMode(ldr,INPUT);
  pinMode(flame,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

}

void loop()
{
  delay(500);

  //IR FLAME SENSOR
  valFlame = digitalRead(flame);  //read sensor value
  if(valFlame == LOW){            //cek apakah sensor LOW
      Firebase.setInt(firebaseData, path + "/flame", 0);
      Firebase.setInt(firebaseData, path + "/buzzer", 1);
  }
  else{
      Firebase.setInt(firebaseData, path + "/flame", 1);
      Firebase.setInt(firebaseData, path + "/buzzer", 0);
  }

  //LDR SENSOR
  valLdr = digitalRead(ldr);  //read sensor LDR
  if(valLdr == HIGH){         //cek apakah sensor HIGH
      Firebase.setInt(firebaseData, path + "/ldr", 1);
      Firebase.setInt(firebaseData, path + "/led", 1);
  }
  else{
      Firebase.setInt(firebaseData, path + "/ldr", 0);
      Firebase.setInt(firebaseData, path + "/led", 0);
  }

  //Menghidupkan BUZZER
  if(Firebase.getInt(firebaseData, path + "/buzzer")){
    if(firebaseData.intData() == 1)
      digitalWrite(buzzer,HIGH);
    else
      digitalWrite(buzzer,LOW);
  }
  
  //Menghidupkan LED
  if(Firebase.getInt(firebaseData, path + "/led")){
    if(firebaseData.intData() == 1)
      digitalWrite(led,HIGH);
    else
      digitalWrite(led,LOW);
  }
}
