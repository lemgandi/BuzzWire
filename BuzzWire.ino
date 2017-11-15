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
#include <limits.h>  // UINT_MAX signal value for timers

#define CHS_DEBUG
#include "BuzzWireTypes.h"
#include "Prototypes.h"

#define STARTPIN 16
#define FAILPIN 17
#define SUCCESSPIN 18

// Type of game, set by ChooseBuzzWireGame.ino . Never "NullGame" after setup.
GameType CurrentGameType=NullGame;


// Our State Machine s State
State CurrentState=Notified;


LiquidCrystal Lcd(8,9,4,5,6,7);


// Millis at start of game
unsigned long StartTime = 0;
// Millis since start of game
unsigned long ElapseTime = 0;
// Seconds next game should last (always the same for Challenge,
// time of last success for Tournament, -1 for Free)
unsigned long TimerInitSec = UINT_MAX;
// Seconds remaining in this game
unsigned long ChallengeTime = UINT_MAX;


#ifdef CHS_DEBUG
void printCurrentState(int nlflag)
{
   char *CurrentStateNames[] = {"Started","Failed","Succeeded","Notified"};
   Serial.print("CurrentState: ");
   Serial.print(CurrentStateNames[CurrentState]);
   Serial.print("(");
   Serial.print(CurrentState);
   if(nlflag)
      Serial.println(")");
   else
      Serial.print(") ");
}
#endif

/*
 * ISR for STARTPIN low
 */
void Start()
{
   StartTime=millis();
   ChallengeTime = TimerInitSec;
   CurrentState=Started;
#ifdef CHS_DEBUG
   printCurrentState(0);
   Serial.print(" Started at ");
   Serial.print(StartTime);
   Serial.print(" ChallengeTime: ");
   Serial.println(ChallengeTime);
#endif   
}
/*
 * ISR for FAILPIN low
 */
void Fail()
{
   if(Started == CurrentState)
      CurrentState=Failed;
#ifdef CHS_DEBUG
   printCurrentState(0);
   Serial.print(" Failed at ");
   Serial.println(ElapseTime);
#endif
}
/*
 * ISR for SUCCESSPIN low
 */
void Success()
{
   if(Started == CurrentState)
      CurrentState=Succeeded;
#ifdef CHS_DEBUG
   printCurrentState(0);
   Serial.print(" Succeeded at ");
   Serial.print(ElapseTime);
   Serial.print(" ChallengeTime:");
   Serial.println(ChallengeTime);
#endif
}

/*
 * Well, did I Win or Lose?  Play a tune here eventually.
 */
void notifyUser(State thestate)
{
   char firstLine[16];
   memset(firstLine,0,sizeof(firstLine));
   String twostLine;
#ifdef CHS_DEBUG
   Serial.print("notifyUser: ");
   printCurrentState(0);
#endif

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
   Lcd.clear();
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
   int elapsed_time= (millis() - StartTime)/1000;
   
   switch(CurrentGameType)
   {
      case Challenge:
         retVal = doTimeCountDown(ElapseTime);
         break;
     case Tournament:
         if(UINT_MAX == TimerInitSec)
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
   /* BuzzWire state machine:
    * Started -- game in progress
    * Succeeded -- user has won
    * Failed  -- user has lost
    * Notified -- music has played, results are displayed, and we are ready for a new game.
    */
#ifdef CHS_DEBUG
   printCurrentState(1);
   delay(250);
#endif
   switch(CurrentState)
   {
      case Started:
         // Have we timed out for Challenge or Tournament yet? Else just display the time.
      	 CurrentState = handleTimer();
         break;
      case Succeeded:
#ifdef CHS_DEBUG
       Serial.println("Succeeded");
#endif
         if(Tournament == CurrentGameType)
	    TimerInitSec = ElapseTime;
	 ChallengeTime = TimerInitSec;
         notifyUser(CurrentState);
	 ElapseTime = 0;	 
	 CurrentState = Notified; 
         break;
      case Failed:
	 ChallengeTime = TimerInitSec;
         notifyUser(CurrentState);
	 ElapseTime = 0;	 
	 CurrentState = Notified;
         break;
      default: //Notified -- wait for start of new game.
         break;
   }
}
 