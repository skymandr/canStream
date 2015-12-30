/*  util.c: A program for parsing arguments and setting up CAN communication
 *  using the Kvaser CANlib API.
 *  Copyright (C) 2016 Andreas Skyman (skymandr (kanelbulle) fripost dot org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UTIL_H_
#define _UTIL_H_

#include <canlib.h>


void check (char* id, canStatus stat);
void printArgHelp (void);
int parseArgs (int argc, char* argv[], int* channel, int* bitrate,
               int* bitrateFd, int* dlc);
canHandle initialise (int channel, int bitrate, int bitrateFd);

#endif
