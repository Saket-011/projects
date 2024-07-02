#include<Servo.h>
//#include<RTClib.h>
#include<Wire.h>

//RTC_DS1307 rtc;

int soilmoisture=0; 
int light=0;
int moisturethreshold = 500;
float angle;
int outsideair;
int insideair;
int pass=0;
//int realtime=0;
Servo myservo;
Servo lightservo;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  myservo.attach(13);
  lightservo.attach(12);
  Serial.begin(9600);
  //Wire.begin();
  //rtc.begin();
}

void loop()
{
  //DateTime now = rtc.now();
  //realtime= now.hour();
  outsideair= analogRead(A2);
  insideair= analogRead(A3);
  
  if (insideair>200)
  {
    myservo.write(90);
    lightservo.write(90);
    digitalWrite(11, LOW);
    digitalWrite(10,HIGH);
    pass =1;
    
    return ;
  }
  else
  {
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    if (pass==1)
    {
      myservo.write(0);
      lightservo.write(0);
      pass=0;
    }
  }
  if (outsideair>200)
  {
    myservo.write(0);
    return;
  }
  soilmoisture = analogRead(A0);
  light = analogRead(A1);

  if (soilmoisture > moisturethreshold)
  {
    myservo.write(0);
    delay(1000);
  }
  else
  {
    myservo.write(90);
  }
  angle = 90.0*(light-28)/901.0;
  lightservo.write(90-angle);
  
  delay(10);
    
}
