#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <SoftwareSerial.h> //tạo cổng serial ảo
SoftwareSerial mySerial(10, 11); // RX, TX
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

String str;
char* str1 = "NHIETDO";
char* str2 = "DOAM";
char* str3 = "BATDEN";
char* str4 = "TATDEN";
int b = 0;

void setup() 
{
//  pinMode(6,OUTPUT); digitalWrite(6,LOW);
//  pinMode(7,OUTPUT); digitalWrite(7,HIGH);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.print("AT+CMGL=\"ALL\"\r\n");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.println(t);
  Serial.println(h);
  lcd.setCursor(0, 0); lcd.print("t="); lcd.setCursor(2, 0); lcd.print(t);
  lcd.setCursor(8, 0); lcd.print("h="); lcd.setCursor(10, 0); lcd.print(h);
  //lcd.setCursor(0, 1);lcd.print("value=");lcd.setCursor(6, 1);lcd.print(light);
  
  if(t>=27)
  {
    mySerial.print("AT+CMGF=1\r\n");
    delay(2000);
    mySerial.print("AT+CMGS=\"01659795596\"\r\n");
    delay(2000);
    mySerial.print("bao dong ");
    mySerial.print("\x1A");
    delay(4000);

    mySerial.print("ATD01659795596;\r\n");
    delay(4000);
  }
  
  str = mySerial.readString();
  char* a = str.c_str();
  if(strstr(a,str1))
  {
      mySerial.print("AT+CMGF=1\r\n");
      delay(2000);
      mySerial.print("AT+CMGS=\"01659795596\"\r\n");
      delay(2000);
      mySerial.print("nhiet do dang la ");
      mySerial.print(t);
      delay(2000);
      mySerial.print("\x1A");
      delay(4000);
  }
  
  if(strstr(a,str2))
  {
      mySerial.print("AT+CMGF=1\r\n");
      delay(2000);
      mySerial.print("AT+CMGS=\"01659795596\"\r\n");
      delay(2000);
      mySerial.print("do am dang la ");
      mySerial.print(h);
      delay(2000);
      mySerial.print("\x1A");
      delay(4000);
  }
  if(strstr(a,str3))
  {
    digitalWrite(LED_BUILTIN, HIGH);
    b = 0;
  }
  if(strstr(a,str4))
  {
    digitalWrite(LED_BUILTIN, LOW);
    b = 0;
  }
  mySerial.print("AT+CMGDA=\"DEL ALL\"\r\n");
}
