#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

MeDCMotor motor_9(M1);
MeDCMotor motor_10(M2);
MeUltrasonicSensor ultraSensor(1);
MePotentiometer potentiometer(3);
Me7SegmentDisplay seg7(2);
MeJoystick joystick(4);
int d = 0;
float change =0;
float x=0;
float y=0;

void setup() {
  // put your setup code here, to run once:
  change =0;
  Serial.begin(9600);
  pinMode(15,INPUT);
  pinMode(14,INPUT);
  pinMode(17,INPUT);
  pinMode(16,INPUT);
  pinMode(18,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  change = potentiometer.read();
  d = ultraSensor.distanceCm();
  x= joystick.read(1);
  y= joystick.read(2);
  delay(300);
  if(d>5){
    seg7.display(float(d));
     motor_9.run(float(-change));
     motor_10.run(float(change));
     if(x>200)
     {
      forward(change);
     }
     else if(x<-200)
     {
      back(change);
     }
     else if(y>200)
     {
      left(change);
     }
     else if(y<-200)
     {
      right(change);
     }
     else
     {
      stopp();
     }
  }
  else{
    if(x<-200)
     {
      back(change);
     }
  }
    
}

void forward (float change){
     motor_9.run(float(-change));
     motor_10.run(float(change));
}

void back (float change){
     motor_9.run(float(change));
     motor_10.run(float(-change));
}

void left (float change){
     motor_9.run(float(change));
     motor_10.run(float(0));
}
void right (float change){
     motor_9.run(float(0));
     motor_10.run(float(-change));
}
void stopp (){
     motor_9.run(0);
     motor_10.run(0);
}
