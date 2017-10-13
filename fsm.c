/*
 * Copyright (C) 2017 Владимир Яворский <vovka@krevedko.su>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "debug.h"
#include "fsm.h" 

State state_e = START;
char *gcode_symbol;
double x;
double y;
double z;
double feed;

void gcodeFSM(char *g_code) {
    int line_number;
    int group_number;
    gcode_symbol = g_code;
    while (state_e != STOP) {
        switch (state_e) {
            case START:
                state_e = GCODE_COMMAND;
                break;
            case GCODE_COMMENT:
                debugf("comment: %s\n", gcode_symbol - 1);
                gcode_symbol = strchr(gcode_symbol, ')');
                state_e = GCODE_COMMAND;
                break;
            case GCODE_LINE_NUMBER:
                line_number = (int) strtol(gcode_symbol, &gcode_symbol, 10);
                debugf("line number: %d\n", line_number);
                state_e = GCODE_COMMAND;
                break;
            case GCODE_COMMAND:
                switch (*gcode_symbol) {
                    case '(':
                        state_e = GCODE_COMMENT;
                        break;
                    case '%':
                        debugf("first frame\n");
                        break;
                    case 'N':
                        state_e = GCODE_LINE_NUMBER;
                        break;
                    case 'G':
                        state_e = GCODE_COMMAND_G;
                        break;
                    case 'X':
                        state_e = GCODE_X;
                        break;
                    case 'Y':
                        state_e = GCODE_Y;
                        break;
                    case 'Z':
                        state_e = GCODE_Z;
                        break;
                    default:
                        debugf("command %c not supported\n", *gcode_symbol);
                        char *next_command = strchr(gcode_symbol, ' ');
                        char *next_frame = strchr(gcode_symbol, '\n');
                        if (next_command > next_frame) {
                            gcode_symbol = next_frame;
                        } else if (next_command != 0) {
                            gcode_symbol = next_command;
                        } else {
                            state_e = STOP;
                            break;
                        }
                        state_e = GCODE_COMMAND;
                }
                break;
            case GCODE_COMMAND_G:
                group_number = (int) strtol(gcode_symbol, &gcode_symbol, 10);
                switch (group_number) {
                    case 0:
                        debugf("G00 rapid\n");
                        state_e = GCODE_COMMAND;
                        break;
                    case 1:
                        debugf("G01 linier\n");
                        state_e = GCODE_COMMAND;
                        break;
                    default:
                        debugf("command G%d not supported\n", group_number);
                        state_e = GCODE_COMMAND;
                }
                break;
            case GCODE_X:
                x = strtof(gcode_symbol, &gcode_symbol);
                debugf("X: %f\n", x);
                state_e = GCODE_COMMAND;
                break;
            case GCODE_Y:
                y = strtof(gcode_symbol, &gcode_symbol);
                debugf("Y: %f\n", y);
                state_e = GCODE_COMMAND;
                break;
            case GCODE_Z:
                z = strtof(gcode_symbol, &gcode_symbol);
                debugf("Z: %f\n", z);
                state_e = GCODE_COMMAND;
                break;
            case GCODE_FEED:
                feed = strtof(gcode_symbol, &gcode_symbol);
                debugf("FEED: %f\n", feed);
                state_e = GCODE_COMMAND;
                break;
        }
        gcode_symbol++;
        if (*gcode_symbol == 0) {
            state_e = STOP;
        }
    }
}
