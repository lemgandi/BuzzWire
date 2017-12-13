#ifndef BUZZWIRETUNES_H
#define BUZZWIRETUNES_H
/*
 * Tunes for the BuzzWire game.  Included if SILENT is not defined.
 * 
 * Copyright(c) Charles Shapiro November 2017

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

#include <pitches.h>
#include <MusicBox.h>

#define STARTSONG 0
static note StartSong[] = {
  {NOTE_C4,8},  {NOTE_D4,8},  {NOTE_E4,8},  {NOTE_G4,8},
  {0,8},  {NOTE_E4,8},  {NOTE_G4,4},  {-1,-1}
};

#define FAILSONG 1
static note FailSong[] = {
   {NOTE_C6,4},   {NOTE_B5,4},   {NOTE_A5,4},   {NOTE_G5,4},
   {NOTE_C4,2},
   {-1,-1}
};

/*
 * Play if we win
 */
#define SUCCESSSONG 2
static note SuccessSong[] =  {
{NOTE_F4,   8},{NOTE_E4,  16},{NOTE_D4,   8},{NOTE_CS4,  16},
{NOTE_C4,   8},{NOTE_B3,  16},{NOTE_AS3,   8},{NOTE_A3,  16},
{NOTE_G3,  16},{NOTE_A3,  16},{NOTE_AS3,  16},{NOTE_A3,   8},
{NOTE_G3,  16},{NOTE_C4,   8},{0,   3,},{NOTE_C4,  12},
{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_GS3,   8},
{NOTE_A3,  16},{NOTE_F4,   8},{NOTE_C4,  16},{NOTE_C4,   8},
{NOTE_A3,  16},{NOTE_AS3,   8},{NOTE_AS3,  16},{NOTE_AS3,   8},
{NOTE_C4,  16},{NOTE_D4,  4},{0,    12},{NOTE_AS3,  12},
{NOTE_G3,  16},{NOTE_G3,  16},{NOTE_G3,  16},{NOTE_FS3,   8},
{NOTE_G3,  16},{NOTE_E4,   8},{NOTE_D4,  16},{NOTE_D4,   8},
{NOTE_AS3,  16},{NOTE_A3,   8},{NOTE_A3,  16},{NOTE_A3,   8},
{NOTE_AS3,  16},{NOTE_C4,  4},{0,  12},{NOTE_C4,  12},
{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_GS3,   8},
{NOTE_A3,  16},{NOTE_A4,   8},{NOTE_F4,  16},{NOTE_F4,   8},
{NOTE_C4,  16},{NOTE_B3,   8},{NOTE_G4,  16},{NOTE_G4,   8},
{NOTE_G4,  16},{NOTE_G4,  4},{0,  16},{NOTE_G4,  12},
{NOTE_E4,  17},{NOTE_G4,  17},{NOTE_G4,  17},{NOTE_FS4,   8},
{NOTE_G4,  12},{NOTE_D4,  17},{NOTE_G4,  17}, {NOTE_G4,  17},
{NOTE_FS4,   8},{NOTE_G4,  16},{NOTE_C4,   8},{ NOTE_B3,  16},
{NOTE_C4,   8},{NOTE_B3,  16},{NOTE_C4,   8},{0,1},
{-1,-1}
};

#endif  //BUZZWIRETUNES_H
