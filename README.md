# Buzzwire Timed

This is an Arduino version of the old chestnut Buzz Wire game. Players
must navigate a loop of wire over a larger wire loop without touching
the two together.

This code uses an Arduino LCD/button shield to make the game a tad
more Interesting.  These popular devices are often available at retail
electronics stores (Fry's and Micro Center both carry them) and on line for
between $10 and $20.  Velleman makes one (VMA203) as does OSEPP
(16x2SHD-01) and Sparkfun (DEV-13293).  I've tested this code on the
Velleman and the OSEPP shields, but I haven't obtained a Sparkfun
shield. Adafruit makes a shield which may be similar, but from their
description it may not work with this code. It's also significantly
more expensive than the other three. All of these shields feature an
LCD with 2 lines of 16 characters each and six push buttons. Five of
them are helpfully labeled (Up/Down,Right/Left, and Select). The sixth
is labeled "Rst" and is tied to the reset pin of the Arduino beneath
the shield.  For less than $30, you can be the proud owner of a tiny
computer, complete with a display, control buttons, and 11 I/O lines.

This BuzzWire game has three modes: Timed, Challenge, and Tournament.
- Timed mode
  - The timer counts up by seconds as you navigate the game.
- Challenge mode
  - You set a time and the timer counts down; you must finish your run before it hits 0.  
- Tournament mode
  - The timer counts up for the first run, but in subsequent runs the timer counts down from the
    time you took for the last run.


Select the mode with the Up/Down/Left/Right/Select buttons on the
VMA203. To change modes, hit the &lt;reset&gt; button. Use
Up/Down/Left/Right/Select to change the time value in Challenge mode.
All games start when you touch the wire loop to the start pin. Win when you
touch the wire loop to the finish pin within the time limit. Lose
by running out of time or by touching the wire loop to the big wire
loop.

## Libraries

By default, BuzzWire uses my [MusicBox library](http://github.com/lemgandi/MusicBox).  You can disable this 
with ```#define SILENT``` in the BuzzWire.ino file.  It also uses [GreyGnome's excellent interrupt library](http://github.com/GreyGnome/EnableInterrupt).


Pins

These shields use many of the Digital pins on the Arduino, as well as
the first Analog pin (pin 14, AKA A0) BuzzWire itself uses the
following pins:

- Pin 16 ( A2) 
  - Connects to a nail at the start of the big loop. Touch this with the wand to start or restart the game. 
- Pin 17 (A3)
  - Connects to the big wire loop.  Touch this one and lose.
- Pin 18 (A4)
  - Connects to a nail at the end of the big loop. Touch the wand to this one to win the game. 
- Ground
  - Connected to the wand (small wire loop) 

If ```SILENT``` is not defined, BuzzWire also uses pin 15 (A1) as a
speaker out pin; the other speaker wire should be connected to ground.


