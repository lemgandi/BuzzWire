/*
 * BuzzWire program -- control LCD display, buttons, game, nails.
 * Free Mode: timer on LCD counts up until success or failure
 * Challenge Mode: Set a time, timer decrements, failure at zero or contact
 * Tournament Mode:  Timer is set to elapsed time of last successful run.
 *
 * Copyright (c) Charles Shapiro, November 2017
 */
#include <EnableInterrupt.h>

#define STARTPIN 16
#define FAILPIN 17
#define SUCCESSPIN 18


int StartedFlag=0;
int FailFlag=0;
int SuccessFlag=0;

typedef enum State {
  Started,
  Failed,
  Succeeded,
  Notified
};

void Start()
{
   StartedFlag = 1;
}
void Fail()
{
   FailFlag = 1;
}
void Success()
{
   
   SuccessFlag = 1;
}
void setup()
{
   Serial.begin(9600);

   pinMode(STARTPIN,INPUT_PULLUP);
   pinMode(FAILPIN,INPUT_PULLUP);
   pinMode(SUCCESSPIN,INPUT_PULLUP);
   
   enableInterrupt(STARTPIN,Start,FALLING);
   enableInterrupt(FAILPIN,Fail,FALLING);
   enableInterrupt(SUCCESSPIN,Success,FALLING);
}

void loop()
{
  Serial.print("Nothing ");
  delay(500);
  
  if(StartedFlag > 0) {
     Serial.println("Started !!!");
     StartedFlag = 0;
  }
  if(FailFlag > 0) {
     Serial.println("Failed !!!");
     FailFlag = 0;
  }
  if(SuccessFlag > 0) {
     Serial.println("Succeeded !!!");
     SuccessFlag = 0;
  }
}
 