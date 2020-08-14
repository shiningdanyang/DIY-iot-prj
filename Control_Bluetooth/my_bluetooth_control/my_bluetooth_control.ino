#include <Servo.h>
#include <SoftwareSerial.h>
Servo volant;
SoftwareSerial bluetooth(11, 12); // RX, TX
int timeset = 1;
const int balance = 90;
const int l_value = 40;
const int r_value = 150;
void setup()
{
  bluetooth.begin(38400);
  volant.attach(4);
  pinMode(2, OUTPUT); digitalWrite(2, LOW);
  pinMode(3, OUTPUT); digitalWrite(3, LOW);
  volant.write(balance);
  Serial.begin(9600);
}

void loop()
{
  if (bluetooth.available())
  {
    char command = bluetooth.read();
    Serial.println(command);
    switch (command)
    {
      case ('S'):
        {
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          volant.write(balance);
          delay(timeset);
          break;
        }
      case ('F'):
        {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          volant.write(balance);
          delay(timeset);
          break;
        }
      case ('B'):
        {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          volant.write(balance);
          delay(timeset);
          break;
        }
      case ('R'):
        {
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          volant.write(r_value);
          delay(timeset);
          break;
        }
      case ('L'):
        {
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          volant.write(l_value);
          delay(timeset);
          break;
        }
      case ('I'):
        {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          volant.write(r_value);
          delay(timeset);
          break;
        }
      case ('G'):
        {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          volant.write(l_value);
          delay(timeset);
          break;
        }
      case ('J'):
        {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          volant.write(r_value);
          delay(timeset);
          break;
        }
      case ('H'):
        {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          volant.write(l_value);
          delay(timeset);
          break;
        }
    }
  }
}
