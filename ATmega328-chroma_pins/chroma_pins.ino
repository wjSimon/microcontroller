/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
*/

#include "TimerOne.h"

int lastAnalog;
int sumAnalog;
int counter;
volatile bool touch;
const int threshold = 1000;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);

    
  for(int i = 3; i <= 8; i++)
  {
     if(i == 6) continue; //pin 6 broken
     delay(200);
     digitalWrite(i, HIGH);
  } 

  delay(1200);
  for(int i = 8; i >= 3; i--)
  {
     if(i == 6) continue; //pin 6 broken
     digitalWrite(i, LOW);
  } 
  
  randomSeed(analogRead(1)); //analog 0 broken
  
  Timer1.initialize(10000);
  Timer1.attachInterrupt(TouchReg); // pollData run @ 2kHz
}

// the loop function runs over and over again forever
void loop() {  
  /* 
  for(int i = 3; i <= 8; i++)
  {
    if(i == 6) continue; //pin 6 broken
     delay(500);
     digitalWrite(i, HIGH);
  } 

  for(int i = 8; i >= 3; i--)
  {
      if(i == 6) continue; //pin 6 broken
     delay(500);
     digitalWrite(i, LOW);
  } 
  /**/ 
  if(!touch)
  {
      delay(10);
      int ps = random(3,8);
      if(ps == 6) ps = 8;
      bool power = random(0,2) != 0;
      digitalWrite(ps, power);

      return;
  }

  for(int i = 8; i >= 3; i--)
  {
     if(!touch) return;
     if(i == 6) continue; //pin 6 broken
     digitalWrite(i, LOW);
  } 

  for(int i = 3; i <= 8; i++)
  {
     if(!touch) return;
     if(i == 6) continue; //pin 6 broken
     delay(200);
     digitalWrite(i, HIGH);
  } 
  
  for(int i = 8; i >= 3; i--)
  {
     if(!touch) return;
     if(i == 6) continue; //pin 6 broken
     delay(200);
     digitalWrite(i, LOW);
  } 
}

void TouchReg()
{
  int analog = analogRead(1);
  int diff = analog - lastAnalog;
  lastAnalog = analog;
  diff = abs(diff);
  sumAnalog += diff;
  counter++;
  
  if(counter >= 10)
  {
    counter = 0;

    touch = sumAnalog >= threshold;
    Serial.println(sumAnalog);
    sumAnalog = 0;
  }
}

