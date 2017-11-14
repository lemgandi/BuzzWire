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


GameType CurrentGameType=NullGame;
State CurrentState=Notified;
LiquidCrystal Lcd(8,9,4,5,6,7);

int StartTime = 0;
int ElapseTime = 0;
int TimerInitSec = -1;
int ChallengeTime =-1;

/*
 * ISR for STARTPIN low
 */
void Start()
{
   StartTime=millis();
   ChallengeTime = TimerInitSec;
   CurrentState=Started;
}
/*
 * ISR for FAILPIN low
 */
void Fail()
{
   if(Started == CurrentState)
      CurrentState=Failed;
}
/*
 * ISR for SUCCESSPIN low
 */
void Success()
{
   if(Started == CurrentState)
      CurrentState=Succeeded;
}
void notifyUser(State thestate)
{
   char firstLine[16];
   memset(firstLine,0,sizeof(firstLine));
   String twostLine;
   
   switch(thestate)
   {
      case Succeeded:
         strncpy(firstLine,"Hurray for You!",sizeof(firstLine)-1);
	 twostLine="Success in ";
	 twostLine.concat(String(ElapseTime));
	 break;
      default: // Failed. Should never be any other state.
         strncpy(firstLine,"Oops. Too Bad.",sizeof(firstLine)-1);
	 if(ElapseTime > ChallengeTime)
	    twostLine = "Too Slow!";
	 else
	    twostLine = "Touched Wire!";
         break;
   }
   Lcd.clear();
   Lcd.write(firstLine);
   Lcd.setCursor(0,1);
   Lcd.write(twostLine.c_str());
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

/*
 *  Display time or time left on LCD
 */
void displayNewTime(int theTime)
{
   Lcd.setCursor(0,1);
   Lcd.write("                ");
   Lcd.setCursor(0,1);
   Lcd.write(String(theTime).c_str());
}

/*
 * Count time down in challenge or tournament mode
 */
State doTimeCountDown(int elapsed_time)
{
   State retVal=Started;

   if(ElapseTime < elapsed_time) {
      ++ElapseTime;
      --ChallengeTime;
   }
   if(ChallengeTime < 1)
      retVal=Failed;
   else
      displayNewTime(ChallengeTime);
      
   return retVal;
}
/*
 *  Do timer.  Decrement for Tournament or Challenge mode, display for timed mode.
 */
State handleTimer(void)
{
   State retVal = Started;
   int elapsed_time=0;
   ElapseTime = (millis() - StartTime)/1000;
   
   switch(CurrentGameType)
   {
      case Challenge:
         retVal = doTimeCountDown(ElapseTime);
         break;
     case Tournament:
         if(-1 == TimerInitSec)
	    displayNewTime(ElapseTime);
	 else
	    retVal=doTimeCountDown(ElapseTime);
      default: // Free
	 if(ElapseTime < elapsed_time) {
	    ++ElapseTime;
	    displayNewTime(ElapseTime);
	 }
         break;
   }
   return retVal;
}
/*
 * Main Line Loop
 */
void loop()
{
   int currentSecs=0;
   switch(CurrentState)
   {
      case Started:
      	 CurrentState = handleTimer();
         break;
      case Succeeded:
         if(Tournament == CurrentGameType)
	    ChallengeTime = ElapseTime;
         notifyUser(CurrentState);
	 CurrentState = Notified; 
         break;
      case Failed:
         notifyUser(CurrentState);
	 CurrentState = Notified;
         break;
      default: //Notified
         break;
   }
}
 