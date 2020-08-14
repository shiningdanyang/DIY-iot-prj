//esp8266
//cảm biến
//blynk
//thingspeak

//cụm khai báo esp8266
#include <ESP8266WiFi.h>
const char* ssid = "FBU-Research";  //tên wifi kết nối đến
const char* pass = "12345678";  //password wifi
WiFiClient  client;

//cụm khai báo cảm biến
float t;
float h;
#include <DHT.h>
#define DHTPIN D4         ////////////////////////////
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//cụm khai báo blynk
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#define PIN_UPTIME1 V5
#define PIN_UPTIME2 V4
char auth[] = "43fe8c56270e48958e0ba614a40c2f12";
BLYNK_READ(PIN_UPTIME1)
{
  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
  Blynk.virtualWrite(PIN_UPTIME1, t);
}

BLYNK_READ(PIN_UPTIME2)
{
  Blynk.virtualWrite(PIN_UPTIME2, h);
}

//cụm khai báo thingspeak
#include "ThingSpeak.h"
unsigned long myChannelNumber = 351226;
const char * myWriteAPIKey = "X5W4E73CXY4ITOJZ";




void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  Serial.println("");
  Serial.println("complete setup blynk");
  
  Serial.println("");
  Serial.println("connected, complete setup ESP");
  
  dht.begin();
  Serial.println("");
  Serial.println("complete setup dht11");

  ThingSpeak.begin(client);
  Serial.println("");
  Serial.println("complete setup thingspeak");



  

}

void loop() 
{
  // put your main code here, to run repeatedly:
  h = dht.readHumidity();
  t = dht.readTemperature();
  Blynk.run();
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  Serial.print("do am ");
  Serial.println(h);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  Serial.print("nhietdo ");
  Serial.println(t);
  delay(1000);
}
