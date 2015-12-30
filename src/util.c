/*  util.c: A program for parsing arguments and setting up CAN communication
 *  using the Kvaser CANlib API.
 *  Copyright (C) 2016 Andreas Skyman <skymandr (kanelbulle) fripost dot orgr>
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


// Functions and definitions for argument parser:

/* The options the parser understands. */
struct argp_option options[] = {
  {"channel",   'c', "CHAN", 0, "CAN channel" },
  {"bitrate",   'b', "BR",   0, "CAN bitrate/CAN FD arbitration bitrate" },
  {"bitratefd", 'f', "BRFD", 0, "CAN FD bitrate" },
  {"dlc",       'l', "DLC",  0, "data length code or number of bytes" },
  { 0 }
};

extern char doc[];

static struct argp argp = { options, parseArg, doc, "" };

error_t parseArg (int key, char* arg, struct argp_state* state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'c':
      arguments->channel = atoi(arg);
      break;
    case 'b':
      arguments->bitrate = atoi(arg);
      break;
    case 'f':
      arguments->bitrateFd = atoi(arg);
      break;
    case 'l':
      arguments->dlc = atoi(arg);
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}

int parseArgs (int argc, char* argv[], struct arguments* arguments)
{
    int i;
    int status = 0;

    status = argp_parse(&argp, argc, argv, 0, 0, &arguments);

    return status;
}


// Functions for CANlib communication:

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

canHandle initHandle (int channel, int bitrate, int bitrateFd)
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
