#ifndef PROTOTYPES_H
#define PROTOTYPES_H
/* 
   ino files get concatenated together in no particular order.  I want to ensure that
   my routines get prototyped correctly no matter what the compiler sees first.
   
   Copyright(c) Charles Shapiro November 2017

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

#include "BuzzWireTypes.h"

GameType chooseGameType(void);

#endif
