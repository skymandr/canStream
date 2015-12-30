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

#include <stdio.h>
#include <signal.h>
#include <canlib.h>

#include "util.h"


void check (char* id, canStatus stat)
{
  char buf[50];

  buf[0] = '\0';
  canGetErrorText(stat, buf, sizeof(buf));
  if (stat != canOK) {
    printf("%s: failed, stat=%d (%s)\n", id, (int)stat, buf);
  } else {
    printf("%s: OK\n", id);
  }
}

void printArgHelp (void)
{
    printf("These are the valid arguments and their default values:\n");
    printf("  -c --channel       (0)    CAN channel\n");
    printf("  -B --bitrate  (100000)    CAN bitrate/FD arbitration bitrate\n");
    printf("  -F --bitratefd     (0)    CAN FD data phase bitrate\n");
    printf("  -l --dlc           (8)     dlc or number of data bytes\n");
}

int parseArgs (int argc, char* argv[], int* channel, int* bitrate,
               int* bitrateFd, int* dlc)
{
    int status = -1;
    return status;
}

canHandle initialise (int channel, int bitrate, int bitrateFd)
{
    canHandle handle;

    /* Allow signals to interrupt syscalls (e.g in canReadBlock) */
    siginterrupt(SIGINT, 1);

    /* Open channel, set parameters and go on bus */
    handle = canOpenChannel(channel, canOPEN_EXCLUSIVE |
                            canOPEN_REQUIRE_EXTENDED);
    if (handle < 0) {
        printf("canOpenChannel %d failed\n", channel);
        return -1;
    }

    /* Make sure to go bus off before setting bus parameters */
    canBusOff(handle);
    check("canSetBusParams", canSetBusParams(handle, bitrate, 0, 0, 0, 0, 0));

    /* If FD bitrate has been specified, set also FD bitrate */
    if (bitrateFd) {
        check("canSetBusParamsFd",
              canSetBusParamsFd(handle, bitrateFd, 0, 0, 0));
    }

    /* Work-around for Leaf bug */
    check("canSetBusOutputControl",
          canSetBusOutputControl(handle, canDRIVER_NORMAL));

    /* Finally, try going bus on */
    check("canBusOn", canBusOn(handle));

    return handle;
}
