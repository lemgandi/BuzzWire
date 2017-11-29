Buzzwire Timed
===

This is an Arduino version of the old chestnut Buzz Wire game. Players
must navigate a loop of wire over a larger wire loop without touching
the two together.  This version uses the Velleman VMA203 LCD/button
shield to make the game a tad more Interesting.  The VMA203 is
available at retail electronics stores (Fry's and Micro Center) and
also on line for about $10.  It features an LCD with 2 lines of 16
characters each and six push buttons. Five of them are helpfully
labeled (Up/Down,Right/Left, and Select). The sixth is labeled "Rst"
and is tied to the reset pin of the Arduino beneath the shield.  For
about $20, you can be the proud owner of a tiny computer, complete
with display and control buttons.

This BuzzWire game has three modes: Timed, Challenge, and Tournament.
- Timed mode: the timer simply counts up by seconds as you navigate
the game. 
- Challenge mode: you set a time and the timer counts
down; you must reach the end of the game before it hits 0.  
- Tournament mode: the timer counts up for the first run, but in
subsequent runs the timer is set to the time you took on the last run,
which you must beat in order to win the game. 

Select the mode with the
up/down buttons on the VMA203. To change modes, hit the &lt;reset&gt;
button.

Press the &lt;down&gt; button on the initial display, then use
Up/Down/Select to choose the game you prefer.  All games start when
you touch the wire loop to the start pin and end when you touch the
wire loop to the finish pin.

# Pins Used

The VMA203 uses most of the Digital pins on the Arduino, as well as the first Analog pin (pin 15, AKA A0)  
BuzzWire itself uses the following pins:

- Pin 16 ( A2) 
  - Connects to a nail at the start of the big loop. Touch this with the wand to start or restart the game. 
- Pin 17 (A3)
  - Connects to the big wire loop.  Touch this one and lose.
- Pin 18 (A4)
  - Connects to a nail at the end of the big loop. Touch the wand to this one to win the game. 
- Ground
  - Connected to the wand (small wire loop) 

If ```SILENT``` is not defined, BuzzWire also uses pin 15 (A1) as a speaker out pin; the other speaker wire 
should be connected to ground.


