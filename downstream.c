/*  downstream: A program for reading data from a CAN bus and printing it to
 *  stdout using the Kvaser CANlib API.
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
#include <canlib.h>

#include "util.h"


void printHelp(void) {
    printf("downstream, version 0.1:\n");
    printf("Copyright (C) 2015  Andreas Skyman\n");
    printf("A program for reading data from stdin and sending it over the\n");
    printf("CAN bus using the Kvaser CANlib API.\n");
    printf("\n");
    printArgHelp();
    printf("\n");
    printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
    printf("This is free software, and you are welcome to redistribute it\n");
    printf("under the terms of the GNU General Public License version 3.\n");
}

int main(int argc, char* argv[]) {
    int channel, bitrate, bitrateFd, dlc;
    int status = 0;
    canHandle handle;

    status = parseArgs(argc, argv, &channel, &bitrate, &bitrateFd, &dlc);
    if (status != 0) {
        printHelp();
        return status;
    }
    handle = initialise(channel, bitrate, bitrateFd);

    return status;
}
