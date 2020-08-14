//https://www.youtube.com/watch?v=mq-bmOwWMWc
#include <SoftwareSerial.h>
#define TX_PIN      7
#define RX_PIN      6 
SoftwareSerial bluetooth(RX_PIN, TX_PIN);
#define A1 8
#define B1 9
#define A2 10
#define B2 11
char buf[3],i;




void setup() 
{
  Serial.begin(38400);
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  bluetooth.begin(38400);

}
void loop() 
{
 
     if (bluetooth.available()) 
     {
      Serial.println(bluetooth.read());
                // đọc chữ liệu
                bluetooth.readBytes(buf,2);
               // delay(500);
               bluetooth.println(buf);
                Check();
                
      }
    
    
   Clear_Buffer();
  
}

void Clear_Buffer()
{
  char i;
    for( i = 0; i < 3; i++)
    {
    buf[i]=0;
    }  
}
void Check()
{
for(i=0;i<3;i++)
   {
  if(buf[i]=='F')
    {

        digitalWrite(13,HIGH);
    }
    else
    if(buf[i]=='B')
    {

        digitalWrite(13,LOW);
    }
    
}
}
