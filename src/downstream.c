/*  downstream: A program for reading data from a CAN bus and printing it to
 *  stdout using the Kvaser CANlib API.
 *  Copyright (C) 2016 Andreas Skyman <skymandr (kanelbulle) fripost dot org>)
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
#include <canlib.h>

#include "util.h"

const char* argp_program_version = "downstream v0.1";

const char* argp_program_bug_address = "<skymandr@fripost.org>";

char doc[] = "A program for reading data from a CAN bus using the Kvaser\n"
             "CANlib API and sending it to stdout\n";


int main(int argc, char* argv[]) {
    int channel, bitrate, bitrateFd, dlc;
    int status = 0;
    canHandle handle;
    struct arguments args;

    // Set default arguments:
    args.channel = 1;
    args.bitrate = 100000;
    args.bitrateFd = 0;
    args.dlc = 8;

    // Parse arguments:
    status = parseArgs(argc, argv, &args);
    if (status != 0) {
        return status;
    }

    // Initialise handle:
    handle = initHandle(channel, bitrate, bitrateFd);

    // If handle was ok, start main loop, else abort:
    if (handle == -1) {
        printf("Could not initialise handle. Aborting...\n");
        status = handle;
    } else {
        printf("Splendid!\n");
    }

    return status;
}
