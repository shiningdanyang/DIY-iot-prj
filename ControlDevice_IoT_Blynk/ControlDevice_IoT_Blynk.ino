//cụm Servo
#include <Servo.h>
Servo locker;
//cụm Thingspeak
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
unsigned long myChannelNumber = 351226;
const char * myWriteAPIKey = "X5W4E73CXY4ITOJZ";
WiFiClient  client;
    
//cụm Blynk
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "73e0a26e11794f2785abc8862a2dc5f1";
char ssid[] = "Duongw";
char pass[] = "87654321";

//cụm cảm biến
#include <DHT.h>
#define DHTPIN 10         ////////////////////////////
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h;
float t;
#define PIN_UPTIME1 V5
#define PIN_UPTIME2 V4

//cụm ánh sáng
float light;
#define PIN_UPTIME3 V6

//cụm nút nhấn
const int ledPin1 = 16;                                //D0
const int btnPin1 = 5;                                 //D1

const int ledPin2 = 4;                                 //D2
const int btnPin2 = 0;                                 //D3

const int ledPin3 = 2;                                 //D4
const int btnPin3 = 14;                                //D5

//const int ledPin4 = 12;                                //D6
//const int btnPin4 = 13;                                //D7

//const int BlynkServerStatus = 15;                     //D7 (led trạng thái kết nối đến blynk server)
void checkPhysicalButton1();
int ledState1 = HIGH;                                   //Khởi đầu với giá trị của ledState==LOW
int btnState1 = LOW;                                    //Khởi đầu với giá trị của btnState==HIGH

void checkPhysicalButton2();
int ledState2 = HIGH;                                   //Khởi đầu với giá trị của ledState==LOW
int btnState2 = LOW;                                    //Khởi đầu với giá trị của btnState==HIGH

void checkPhysicalButton3();
int ledState3 = HIGH;                                   //Khởi đầu với giá trị của ledState==LOW
int btnState3 = LOW;                                    //Khởi đầu với giá trị của btnState==HIGH

void checkPhysicalButton4();
int ledState4 = HIGH;                                   //Khởi đầu với giá trị của ledState==LOW
int btnState4 = LOW;                                    //Khởi đầu với giá trị của btnState==HIGH


BLYNK_READ(PIN_UPTIME1)
{
  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
  Blynk.virtualWrite(PIN_UPTIME1, t);
}

BLYNK_READ(PIN_UPTIME2)
{
  Blynk.virtualWrite(PIN_UPTIME2, h);
}

BLYNK_READ(PIN_UPTIME3)
{
  Blynk.virtualWrite(PIN_UPTIME3, light);
}

BlynkTimer timer;


// Every time we connect to the cloud...
BLYNK_CONNECTED()
{
  // Request the latest state from the server
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  // Alternatively, you could override server state using:
  //Blynk.virtualWrite(V0, ledState);
}

// When App button is pushed - switch the state 
// Khi App button nhấn, chuyển trạng thái
BLYNK_WRITE(V0)
{
  ledState1 = param.asInt();
  digitalWrite(ledPin1, !ledState1);
}

BLYNK_WRITE(V1)
{
  ledState2 = param.asInt();
  digitalWrite(ledPin2, !ledState2);
}

BLYNK_WRITE(V2)
{
  ledState3 = param.asInt();
  digitalWrite(ledPin3, !ledState3);
}

// Kiểm tra trạng thái nút nhấn vật lý
void checkPhysicalButton1()
{
  if (digitalRead(btnPin1) == LOW)
  {
    // btnState is used to avoid sequential toggles
    if (btnState1 != LOW)
    {
      // Toggle LED state
      ledState1 = !ledState1;
      digitalWrite(ledPin1, !ledState1);

      // Update Button Widget
      Blynk.virtualWrite(V0, ledState1);
    }
    btnState1 = LOW;
  }
  else 
  {
    btnState1 = HIGH;
  }
}

void checkPhysicalButton2()
{
  if (digitalRead(btnPin2) == LOW)
  {
    // btnState is used to avoid sequential toggles
    if (btnState2 != LOW)
    {

      // Toggle LED state
      ledState2 = !ledState2;
      digitalWrite(ledPin2, !ledState2);

      // Update Button Widget
      Blynk.virtualWrite(V1, ledState2);
    }
    btnState2 = LOW;
  }
  else 
  {
    btnState2 = HIGH;
  }
}

void checkPhysicalButton3()
{
  if (digitalRead(btnPin3) == LOW)
  {
    // btnState is used to avoid sequential toggles
    if (btnState3 != LOW)
    {

      // Toggle LED state
      ledState3 = !ledState3;
      digitalWrite(ledPin3, !ledState3);

      // Update Button Widget
      Blynk.virtualWrite(V2, ledState3);
    }
    btnState3 = LOW;
  }
  else 
  {
    btnState3 = HIGH;
  }
}

void calculate()
{
  h = dht.readHumidity();
  Serial.println("doam");
  Serial.println(h);
  t = dht.readTemperature();
  Serial.println("nhietdo");
  Serial.println(t);  
}

void calculateLight()
{
  light=analogRead(A0);
  Serial.println(light);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  locker.attach(D8);

//  ThingSpeak.begin(client);
  
  Blynk.begin(auth,ssid,pass);
  pinMode(ledPin1, OUTPUT);
  pinMode(btnPin1, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(btnPin2, INPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(btnPin3, INPUT);
  pinMode(12, OUTPUT);
//  pinMode(btnPin4, INPUT);    
  
  
  timer.setInterval(1L, checkPhysicalButton1);
  timer.setInterval(1L, checkPhysicalButton2);
  timer.setInterval(1L, checkPhysicalButton3);
  //timer.setInterval(1L, checkPhysicalButton4);
  timer.setInterval(1000L,calculate);
  timer.setInterval(1000L,calculateLight);
}

void loop()
{
  
  Blynk.run();
  timer.run();
  if(digitalRead(D0))
    locker.write(60);
  else
    locker.write(180);
  if(light<=70)
    digitalWrite(D6,HIGH);
  else
    digitalWrite(D6,LOW);
}

//void Thingspeak()
//{
////  if((unsigned long) (millis() - writeTime) > 20000)
////    {
////      writeTime = millis();
//      ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey); 
//      ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
////      }
//}

