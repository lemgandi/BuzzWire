/*
 * Display a gametype menu on the lcd screen,then select a game type from it.
 * Called from setup().
 * Copyright (c) Charles Shapiro November 2017

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
 
#include <LiquidCrystal.h>

#include "BuzzWireTypes.h"
#include "Prototypes.h"
#include "buttonValues.h"

typedef struct menuOption {
   char firstLine[16];
   char twostLine[16];
   GameType theChoice;
};

menuOption Options[] =
{
   {"Timed","Show Timer",Free},
   {"Challenge","Set Timer",Challenge},
   {"Tournament","Timer=last run",Tournament}
};

#define OPTION_LEN (sizeof(Options)/sizeof(menuOption))


#ifdef CHS_DEBUG
/*
 * What button got pressed?
 */
void print_button_type(Button thebutton,int line)
{
   char *buttonTypes[] = {"Right","Up","Down","Left","Select","NullButton"};
   if(line)
      Serial.println(buttonTypes[thebutton]);
   else
      Serial.print(buttonTypes[thebutton]);
}
#endif

/*
 * Read a button from the VMA203
 */
Button readButton()
{
   Button theButton=NullButton;
   int keyValue=analogRead(0);

   while(keyValue < SELECTBUTTONMAX)  // Do not read value on a button already pressed.
      keyValue=analogRead(0);
      
   while(theButton == NullButton) {
      keyValue=analogRead(0);
 
      if(keyValue < RIGHTBUTTONMAX)
         theButton=Right;
      else if (keyValue < UPBUTTONMAX)
         theButton=Up;
      else if (keyValue < DOWNBUTTONMAX)
         theButton=Down;
      else if (keyValue < LEFTBUTTONMAX)
         theButton=Left;
      else if (keyValue < SELECTBUTTONMAX)
         theButton = Select;
   }
   
   return theButton;
}


/*
 *  Read right/left button presses
 */
int incDecButton(void)
{
   int retVal=0;
   Button buttonPressed=NullButton;

   while(NullButton == buttonPressed) {
   
   buttonPressed=readButton();
      
   switch(buttonPressed)
   {
      case Up:
      case Right:
         retVal = 1;
         break;
      case Down:
      case Left:
         retVal = -1;
	 break;
      case Select:
         retVal = 0;
	 break;
      default:   // NullButton
	 break;
      }
   }
   return retVal;
}

/*
 * Set time for timer to count down from in Challenge mode
 */
int setChallengeTime(void)
{
   int retVal = 19;
   int addAmt = 1;
   
   Lcd.clear();
   Lcd.print("Set Time (r/l)");

   while (addAmt)
   {
      retVal += addAmt;      
      Lcd.setCursor(0,1);
      Lcd.write("                ");
      Lcd.setCursor(0,1);
      Lcd.write(String(retVal).c_str());
      if(! retVal)
         retVal = 20;
      addAmt = incDecButton();
   }

   return retVal;
}

/*
 * Display menu, get type of game we wish to play
 */
GameType displayMenu()
{
   GameType retVal=NullGame;
   menuOption *currentDisplayedChoice=Options;
   Button currentButton=NullButton;
   Button lastButton=NullButton;
   
   while(NullGame == retVal)
   {
      Lcd.clear();
      Lcd.print(currentDisplayedChoice->firstLine);
      Lcd.setCursor(0,1);
      Lcd.print(currentDisplayedChoice->twostLine);
#ifdef CHS_DEBUG
Serial.println("Bink");
#endif
/*
      while((currentButton != Select) && (currentButton != Up) && (curentButton != Down)) {
         currentButton=NullButton;
         currentButton=readButton();
      }
*/
      while(NullButton == currentButton)
         currentButton = readButton();
	 
      switch(currentButton) {
         case Left:
         case Up:
   	    --currentDisplayedChoice;
   	    if(currentDisplayedChoice < Options)
   	       currentDisplayedChoice = &Options[OPTION_LEN-1];
	    break;
	 case Right:
	 case Down:
	    ++currentDisplayedChoice;
	    if(currentDisplayedChoice > &Options[OPTION_LEN-1])
	       currentDisplayedChoice = Options;
	    break;
	 default: //Select
	    retVal=currentDisplayedChoice->theChoice;
#ifdef CHS_DEBUG
            Serial.print("Selected: ");
	    Serial.println(retVal);
#endif
	    break;
   	 
      }
      currentButton=NullButton;
   }
   return retVal;
}

/*
 * What type of game are we playing?
 * Main line of this file
 */
GameType chooseGameType(void)
{
   Button buttonPressed=NullButton;
   GameType theGameType;


   Lcd.clear();
   Lcd.print("Choose Game Type");
   Lcd.setCursor(0,1);
   Lcd.print("(up/down/select)");
   
   while(NullButton == buttonPressed) {
     buttonPressed=readButton();
   }
   theGameType=displayMenu();
   if(Challenge == theGameType)
      TimerInitSec = setChallengeTime();
   else
      TimerInitSec = -1;
   ChallengeTime = TimerInitSec;
   Lcd.clear();
   Lcd.write("Touch Start");
   Lcd.setCursor(0,1);
   Lcd.write("to Start Game");
   
   return theGameType; 
}
