#include <Servo.h>   //servo library
Servo servo;    

const int trigPin1 = 8; 
const int echoPin1 = 9; 
const int trigPin2 =11;
const int echoPin2 =12;

const int esp = 7;
#define servoPin  6
const int red=5;
const int green=10;   
long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;
int count = 0;

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}
void setup() {
pinMode(red,OUTPUT);
pinMode(green,OUTPUT);
pinMode(esp,OUTPUT);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
Serial.begin(9600); 
}
void loop() {
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
Serial.println("Distance1:");
Serial.println(RightSensor);
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;
Serial.println("Distance2:");
Serial.println(LeftSensor);
digitalWrite(green, HIGH); 
if (LeftSensor < 30) {//in front any object is availabe or not
    if(RightSensor <=13){//garbage checker
    servo.attach(servoPin);
    delay(1);
    servo.write(0);
    while(LeftSensor<30)//while the object is available in front of the dustbin
    {
        SonarSensor(trigPin2, echoPin2);
        LeftSensor = distance;
        Serial.println("object is present in front of me");
    }  
    delay(2000);     
    servo.write(90);    
    delay(1000);
    servo.detach();     
    } 
  }
if(RightSensor<=14)
{
  count = 1 ;   
  digitalWrite(green, LOW); 
  digitalWrite(red, HIGH); 
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.print("Inside loop ");

  if (count > 0 && count < 2)
  {
    digitalWrite( esp, HIGH) ;
      Serial.print("Inner loop ");
    count =count+1 ;
  }
}
else
{
  count == 0 ;
  digitalWrite(red, LOW); 
  digitalWrite(green, HIGH); 
  digitalWrite(esp, LOW); 
  digitalWrite(LED_BUILTIN, LOW); 
}
  delay(1000);
}