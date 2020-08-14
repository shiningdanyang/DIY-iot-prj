#include <Servo.h>

const int trigPin = 5;
const int echoPin = 7;

int IN1 = 13;
int IN2 = 12;
int ENA = 6;
int ENB = 11;
int IN3 = 9;
int IN4 = 8;

int LED = 4;
int Coi = 2;
int phu ;
#define maximumSpeed 190
#define maximum_distance 200
long duration;
int distance;
String readString;
Servo servo_motor;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (LED, OUTPUT);
  pinMode (Coi, OUTPUT);
  Serial.begin(9600);
  servo_motor.attach(3);
  servo_motor.write(90);
  delay(2000);
}

void loop()
{
restart:
  while (Serial.available())
  {
    delay(50);
    char c = Serial.read();
    readString += c;
  }

  if (readString.length() > 0)
  {
    Serial.println(readString);
    if ((readString == "TuDongTat") || (readString == "TuDongTatTat") || (readString == "TuDongTatTatTat") || (readString == "TuDongTatTatTatTat") || (readString == "TuDongTatTatTatTatTat")) 
    {
      phu = 0;
      delay(200);
      readString = "";
      digitalWrite(Coi, HIGH);
      delay(200);
      digitalWrite(Coi, LOW);
      delay(200);
      digitalWrite(Coi, HIGH);
      delay(200);
      digitalWrite(Coi, LOW);
      delay(200);
      Serial.println("phu = 0");
    }
    if (readString == "TuDong")
    {
      phu = 1;
      delay(50);
      Serial.println("phu = 1");
      delay (50);
    }
    ///////////////////////////////////////////////////
    if ((phu == 1) || (readString == "TuDong"))
    {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      int distanceRight = 0;
      int distanceLeft = 0;
      delay(50);
      Serial.print(distance);
      Serial.println("cm");
      Serial.print(distanceRight);
      Serial.println("cm");
      Serial.print(distanceLeft);
      Serial.println("cm");
      delay(500);
      if (distance > 40)
      {
        TienLen();
        delay(1000);
        Dung();
        delay(200);
      }
      if (distance <= 40)
      {
        Dung();
        delay(300);
        LuiVe();
        delay(400);
        Dung();
        delay(300);
        distanceRight = lookRight();
        delay(300);
        distanceLeft = lookLeft();
        delay(300);
        if (distance >= distanceLeft)
        {
          rePhai();
          delay(500);
          Dung();
        }
        else {
          reTrai();
          delay(500);
          Dung();
        }
      }
      goto restart;

    }
    /////////////////////////////////////////////
    if (readString == "Tien")
    {
      TienLen();
    }

    if (readString == "Lui")
    {
      LuiVe();
    }

    if (readString == "Trai")
    {
      reTrai();
    }

    if (readString == "Phai")
    {
      rePhai();
    }

    if (readString == "Ngung")
    {
      Dung();
    }

    if (readString == "BatD")
    {
      digitalWrite (LED, HIGH);
    }

    if (readString == "TatD")
    {
      digitalWrite (LED, LOW);
    }

    if (readString == "Coi")
    {
      digitalWrite(Coi, HIGH);
    }

    if (readString == "TatCoi")
    {
      digitalWrite(Coi, LOW);
    }

    readString = "";
  }
}
int measure()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  delay(300);
  return  distance;
}

int lookRight()
{
  servo_motor.write(20);
  delay(500);
  int  distance = measure();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft()
{
  servo_motor.write(170);
  delay(500);
  int  distance = measure();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

void TienLen()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++)
  {
    analogWrite(ENA, motorSpeed);
    //analogWrite(ENB, motorSpeed);
  }
}

void  LuiVe()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  for (int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++)
  {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }
}

void reTrai()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  for (int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++)
  {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }
}

void rePhai()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++)
  {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }
}

void Dung()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

