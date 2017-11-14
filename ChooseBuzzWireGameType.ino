/*
 * Display a gametype menu on the lcd screen,then select a game type from it.
 * Called from setup().
 */
#include "BuzzWireTypes.h"
#include "Prototypes.h"

#ifdef CHS_DEBUG
/*
 * What button got pressed?
 */
void print_button_type(Button thebutton)
{
   char *buttonTypes[] = {"Right","Up","Down","Left","Select","Null"};
   Serial.print(buttonTypes[thebutton]);
}
#endif
/*
 * Read a button from the VMA203
 */
Button readButton()
{
   Button theButton=NullButton;
   int keyValue;
   
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
 * What type of game are we playing?
 */
GameType chooseGameType(void)
{
   Button buttonPressed=NullButton;
   Lcd.setCursor(0,0);
   //         012345678901234567890123456789012
   Lcd.print("Choose Game Type");
   Lcd.setCursor(0,1);
   Lcd.print("(up/down/select)");
   while(buttonPressed != Down) {
     buttonPressed=readButton();
#ifdef CHS_DEBUG
   print_button_type(buttonPressed);
#endif
   }
   
}
