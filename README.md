Buzzwire Timed
===

This is an Arduino version of the old chestnut Buzz Wire game. Players must
navigate a loop of wire over a wire over a larger wire loop
without touching the two together.  This version uses the
Velleman VMA203 LCD/button shield to make the game a tad more
Interesting.  The VMA203 is available at retail electronics stores
(Fry's and Micro Center) and also on line for about $10.  It features
an LCD with 2 lines of 16 characters each and six push buttons. Five
of them are helpfully labeled (Up/Down,Right/Left, and Select). The
sixth is labeled "Rst" and is tied to the reset pin of the Arduino
beneath the shield.  For about $20, you can be the proud owner of a
tiny computer, complete with display and control buttons.

This BuzzWire game has three modes: Timed, Challenge, and Tournament.
In Timed mode, the timer simply counts up by seconds as you navigate
the game.  In Challenge mode, you set a time and the timer counts
down; you must reach the end of the game before it hits 0.  In
Tournament mode, the timer counts up for the first run, but in
subsequent runs the timer is set to the time you took on the last run,
which you must beat in order to win the game.

Press the <down> button on the initial display, then use
Up/Down/Select to choose the game you prefer.  All games start when
you touch the wire loop to the start pin and end when you touch the
wire loop to the finish pin.



