/*
 * BuzzWire program -- control LCD display, buttons, game, nails.
 * Free Mode: timer on LCD counts up until success or failure
 * Challenge Mode: Set a time, timer decrements, failure at zero or contact
 * Tournament Mode:  Timer is set to elapsed time of last successful run.
 *
 * Copyright (c) Charles Shapiro, November 2017
 */
#include <EnableInterrupt.h>
#include <LiquidCrystal.h>

#define CHS_DEBUG
#include "BuzzWireTypes.h"
#include "Prototypes.h"

#define STARTPIN 16
#define FAILPIN 17
#define SUCCESSPIN 18


int StartedFlag=0;
int FailFlag=0;
int SuccessFlag=0;

GameType CurrentGameType=NullGame;
State CurrentState=Notified;
LiquidCrystal Lcd(8,9,4,5,6,7);

int ElapseTimer = 0;
int TimerInitSec = -1;

/*
 * ISR for STARTPIN low
 */
void Start()
{
   StartedFlag = 1;
}
/*
 * ISR for FAILPIN low
 */
void Fail()
{
   FailFlag = 1;
}
/*
 * ISR for SUCCESSPIN low
 */
void Success()
{   
   SuccessFlag = 1;
}
/*
 * Main Line Setup
 */
void setup()
{
#ifdef CHS_DEBUG
   Serial.begin(9600);
#endif
   Lcd.begin(16,2);
   
   pinMode(STARTPIN,INPUT_PULLUP);
   pinMode(FAILPIN,INPUT_PULLUP);
   pinMode(SUCCESSPIN,INPUT_PULLUP);
   
   enableInterrupt(STARTPIN,Start,FALLING);
   enableInterrupt(FAILPIN,Fail,FALLING);
   enableInterrupt(SUCCESSPIN,Success,FALLING);
   CurrentGameType=chooseGameType();
   #ifdef CHS_DEBUG
   Serial.print("CurrentGameType: ");
   Serial.print(CurrentGameType);
   Serial.print(" TimerInitSec: ");
   Serial.println(TimerInitSec);
#endif

}

void loop()
{
}
 