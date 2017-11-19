#ifndef BUZZWIRE_TYPES
#define BUZZWIRE_TYPES
/*
 * Various useful types for BuzzWire game
 *
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

// State machine states
typedef enum State {
  Started,
  Failed,
  Succeeded,
  Notified
};

// What kind of game we are playing
typedef enum GameType {
   NullGame,
   Challenge,
   Tournament,
   Free
};

// Buttons on the VMA203 shield
typedef enum Button {
   Right,
   Up,
   Down,
   Left,
   Select,
   NullButton
};
#endif
