/*
 * Display a gametype menu on the lcd screen,then select a game type from it.
 * Called from setup().
 * Copyright (c) Charles Shapiro November 2017
 */
#include <LiquidCrystal.h>

#include "BuzzWireTypes.h"
#include "Prototypes.h"

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

#define OPTION_LEN sizeof(Options)/sizeof(menuOption)


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

   while(keyValue < 900)  // Do not read value on a button already pressed.
      keyValue=analogRead(0);
      
   while(theButton == NullButton) {
      keyValue=analogRead(0);
 
      if(keyValue < 64)
         theButton=Right;
      else if (keyValue < 128)
         theButton=Up;
      else if (keyValue < 300)
         theButton=Down;
      else if (keyValue < 500)
         theButton=Left;
      else if (keyValue < 900)
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
   
   while((buttonPressed != Right) && (buttonPressed != Left) && (buttonPressed != Select))
      buttonPressed=readButton();
      
   switch(buttonPressed)
   {
      case Right:
         retVal =1;
	 break;
      case Left:
         retVal = -1;
	 break;
      default:   // Select
         retVal=0;
	 break;
   }
   return retVal;
}

/*
 * Set time for timer to count down from in Challenge mode
 */
int setChallengeTime(void)
{
   int retVal = 0;
   int addAmt = 0;
   
   Lcd.clear();
   Lcd.print("Set Time (r/l)");

   while((0 == retVal) || (addAmt))
   {
      retVal += addAmt;      
      Lcd.setCursor(0,1);
      Lcd.write("                ");
      Lcd.setCursor(0,1);
      Lcd.write(String(retVal).c_str());
      if(retVal < 0)
         retVal = 0;
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
      while((currentButton != Up) && (currentButton != Down) && (currentButton != Select)) {
         currentButton=NullButton;
         currentButton=readButton();
      }
      switch(currentButton) {
         case Up:
   	    --currentDisplayedChoice;
   	    if(currentDisplayedChoice < Options)
   	       currentDisplayedChoice = &Options[OPTION_LEN-1];
	    break;
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
   while(buttonPressed != Down) {
     buttonPressed=readButton();
   }
   theGameType=displayMenu();
   if(Challenge == theGameType)
      TimerInitSec = setChallengeTime();
   ChallengeTime = TimerInitSec;
   Lcd.clear();
   Lcd.write("Touch Start");
   Lcd.setCursor(0,1);
   Lcd.write("to Start Game");
   
   return theGameType; 
}
