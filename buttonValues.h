#ifndef BUTTONVALUES_H
#define BUTTONVALUES_H

/*
 * Button values for Velleman VMA203, OSEPP 16X2SHD-01, and Sparkfun
 * DEV-13293 shields.  These shields all use pin A0 (aka 15 ) to read
 * buttons, using varying resistance on the analog line to figure out
 * which button was pressed.  These values are max values for a 
 * range. I've tested the OSEPP and Velleman boards with them and they
 * appear to work. I've not worked with the Sparkfun board; if you
 * have and these values need to change, please send me a Pull request
 * and I'll add the necessary changes here.
 
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

#define RIGHTBUTTONMAX 64
#define UPBUTTONMAX 128
#define DOWNBUTTONMAX 300
#define LEFTBUTTONMAX 500
#define SELECTBUTTONMAX 900

#endif
