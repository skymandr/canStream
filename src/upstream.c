/*  upstream: A program for reading data from stdin and sending it over a
 *  CAN bus using the Kvaser CANlib API.
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
#include <canlib.h>

#include "util.h"

const char* argp_program_version = "upstream v0.1";

const char* argp_program_bug_address = "<skymandr@fripost.org>";

char doc[] = "A program for reading data from stdin and sending it over the\n"
             "CAN bus using the Kvaser CANlib API.";


int main (int argc, char* argv[]) {
    int channel, bitrate, bitrateFd, i;
    unsigned int dlc;
    unsigned char data[64] = {0};
    int status = 0;
    canHandle handle;
    struct arguments args;

    // Set default arguments:
    args.channel = 0;
    args.bitrate = 1000000;
    args.bitrateFd = 0;
    args.dlc = 8;
    args.id = 42;
    args.timeout = 256;

    // Parse arguments:
    status = parseArgs(argc, argv, &args);
    if (status != 0) {
        return status;
    }

    // CAN FD is not yet implemented...
    if (args.bitrateFd != 0) {
        printf("CAN FD not yet implemented, sorry...\n");
        printf("Will try to proceed with classic CAN!\n");
    }

    // Initialise handle:
    handle = initHandle(args.channel, args.bitrate, args.bitrateFd);

    // If handle was ok, start main loop, else abort:
    if (handle == -1) {
        printf("Could not initialise handle. Aborting...\n");
        status = handle;
    } else {
        printf("Splendid! Will now listen to stdin and send what I find.\n");
        printf("Press ^C to quit.\n");
        while(status == 0) {
            for(i = 0; i < args.dlc; i++) {
                data[i] = getchar();
            }
            status = canWrite(handle, args.id, data, args.dlc, 0);
            status = canWriteSync(handle, args.timeout);
        }
        check("canClose", canClose(handle));
    }

    return status;
}
