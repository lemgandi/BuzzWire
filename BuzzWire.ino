/*
 * BuzzWire program -- control LCD display, buttons, game, nails.
 * Free Mode: timer on LCD counts up until success or failure
 * Challenge Mode: Set a time, timer decrements, failure at zero or contact
 * Tournament Mode:  Timer is set to elapsed time of last successful run.
 *
 * Copyright (c) Charles Shapiro, November 2017

    This file is part of BuzzWire.

    BuzzWire is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BuzzWire is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BuzzWire.  If not, see <http://www.gnu.org/licenses/>.

 */
#include <EnableInterrupt.h>
#include <LiquidCrystal.h>

/*
Define SILENT to make this game silent.  Otherwise, use the MusicBox library
( http://github.com/lemgandi/MusicBox ) for the tunes.
*/

// #define SILENT     

#ifdef SILENT
#pragma message ("SILENT defined. This game will not sing.")
#endif

/*
 * Define CHS_DEBUG to log various things to Serial
 */
// #define CHS_DEBUG 
#include "BuzzWireTypes.h"
#include "Prototypes.h"
#ifndef SILENT
#include "BuzzWireTunes.h"
#include <MusicBox.h>
#endif

#define STARTPIN 16
#define FAILPIN 17
#define SUCCESSPIN 18

// Type of game, set by ChooseBuzzWireGame.ino . Never "NullGame" after setup.
GameType CurrentGameType=NullGame;


// Our State Machine s State
State CurrentState=Notified;

LiquidCrystal Lcd(8,9,4,5,6,7);

#ifndef SILENT
#define MUSIC_PIN 15

MusicBox MusicPlayer(MUSIC_PIN);
#endif

// Millis at start of game
unsigned long StartTime = 0;
// Millis since start of game
int ElapseTime = 0;
// Seconds next game should last (always the same for Challenge,
// time of last success for Tournament, -1 for Free)
int TimerInitSec = -1;
// Seconds remaining in this game
int ChallengeTime = -1;
// Has the time expired yet?
boolean TimerExpired=false;
// Has start song been played on start?
#ifndef SILENT
boolean StartSongPlayed = false;
#endif




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
#ifndef SILENT
   StartSongPlayed = 0;
#endif

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
   String twostLine;
   
#ifdef CHS_DEBUG
   Serial.print("notifyUser: ");
   printCurrentState(0);
#endif

   memset(firstLine,0,sizeof(firstLine));
 
   if(Succeeded == thestate) {
      strncpy(firstLine,"Hurray for You!",sizeof(firstLine)-1);
      twostLine="Success ";
      twostLine.concat(String(ElapseTime));
      twostLine.concat(" sec");
   }
   else {  //Failed. Should never be any other state
      strncpy(firstLine,"Oops. Too Bad.",sizeof(firstLine)-1);
#ifdef CHS_DEBUG
   printCurrentState(0);
   Serial.print(" ChallengeTime: ");
   Serial.print(ChallengeTime);
   Serial.print(" ElapseTime:");
   Serial.print(ElapseTime);
#endif
      if(TimerExpired)
         twostLine = "Too Slow!";
      else
	 twostLine = "Touched Wire!";         
   }
   Lcd.clear();
   Lcd.write(firstLine);
   Lcd.setCursor(0,1);
   Lcd.write(twostLine.c_str());
#ifndef SILENT   
   if(Succeeded == thestate)
      MusicPlayer.playATune(SUCCESSSONG);
   else
      MusicPlayer.playATune(FAILSONG);
   StartSongPlayed = false;
#endif      
}


/*
 *  Display time or time left on LCD
 */
void displayNewTime(int theTime,char *firstLine)
{
   Lcd.clear();
   Lcd.setCursor(0,0);
   Lcd.write(firstLine);
   Lcd.setCursor(0,1);
   Lcd.write("                ");
   Lcd.setCursor(0,1);
   Lcd.write(String(theTime).c_str());
}

/*
 * Count time down in challenge or tournament mode
 */
boolean doTimeCountDown(int elapsed_time)
{
   boolean retVal=false;

   if(ElapseTime < elapsed_time) {
      ++ElapseTime;
      --ChallengeTime;
      if(ChallengeTime <= 0)
         retVal=true;
      else
         displayNewTime(ChallengeTime,"Time Left.Hurry!");
   }
   return retVal;
}

/*
 *  Do timer.  Decrement for Tournament or Challenge mode, display for timed mode.
 */
boolean handleTimer(void)
{
   boolean retVal = false;
   

   int elapsed_time= (int)((millis() - StartTime)/1000);
   
   switch(CurrentGameType)
   {
      case Challenge:
        retVal = doTimeCountDown(elapsed_time);
        break;
     case Tournament:
        if(-1 == TimerInitSec) {
	      if(ElapseTime < elapsed_time) {
	         ++ElapseTime;
	         displayNewTime(ElapseTime,"Time to Beat!");
              }
	   }
	  else
	     retVal=doTimeCountDown(elapsed_time);
      default: // Free
	    if(ElapseTime < elapsed_time) {
	       ++ElapseTime;
	       displayNewTime(ElapseTime,"Time So Far");
	    }
         break;
   }
   return retVal;
}



/***********************************************************************************************/
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
#ifndef SILENT
   MusicPlayer.loadATune(StartSong,STARTSONG);
   MusicPlayer.loadATune(FailSong,FAILSONG);
   MusicPlayer.loadATune(SuccessSong,SUCCESSSONG);
#endif

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
   if((Started == CurrentState) && (TimerExpired))
      CurrentState = Failed;
   switch(CurrentState)
   {
      case Started:
#ifndef SILENT
	 if(! StartSongPlayed) {
	    MusicPlayer.playATune(STARTSONG);
	    StartSongPlayed=true;
	 }
#endif
         // Have we timed out for Challenge or Tournament yet? Else just display the time.
      	 TimerExpired = handleTimer();
         break;
      case Succeeded:
#ifdef CHS_DEBUG
       Serial.println("Succeeded");
#endif
         if(Tournament == CurrentGameType)
	    TimerInitSec = ElapseTime;
	 ChallengeTime = TimerInitSec;
         notifyUser(CurrentState);
	 TimerExpired=false;
	 ElapseTime = 0;	 
	 CurrentState = Notified; 
         break;
      case Failed:
	 ChallengeTime = TimerInitSec;
         notifyUser(CurrentState);
	 TimerExpired=false;
	 ElapseTime = 0;	 
	 CurrentState = Notified;
         break;
      default: //Notified -- wait for start of new game.
         break;
   }
}
 