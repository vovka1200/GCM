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
#include "states.h" 

extern int state;
char *gcode_symbol;
double x;
double y;
double z;
double feed;

void gcode_fsm(char *g_code) {
    int line_number;
    int group_number;
    gcode_symbol = g_code;
    while (state != STATE_END) {
        switch (state) {
            case STATE_COMMENT:
                debugf("STATE_COMMENT: %s\n", gcode_symbol - 1);
                gcode_symbol = strchr(gcode_symbol, ')');
                state = STATE_COMMAND_GROUP;
                break;
            case STATE_LINE_NUMBER:
                line_number = (int) strtol(gcode_symbol, &gcode_symbol, 10);
                debugf("STATE_LINE_NUMBER: %d\n", line_number);
                state = STATE_COMMAND_GROUP;
                break;
            case STATE_COMMAND_GROUP:
                switch (*gcode_symbol) {
                    case '(':
                        state = STATE_COMMENT;
                        break;
                    case '%':
                        debugf("STATE_FIRST_FRAME\n");
                        break;
                    case 'N':
                        state = STATE_LINE_NUMBER;
                        break;
                    case 'G':
                        state = STATE_COMMAND_GROUP_G;
                        break;
                    case 'X':
                        state = STATE_X;
                        break;
                    case 'Y':
                        state = STATE_Y;
                        break;
                    case 'Z':
                        state = STATE_Z;
                        break;
                    default:
                        debugf("STATE_COMMAND_GROUP: not supported %c\n", *gcode_symbol);
                        char *next_command = strchr(gcode_symbol, ' ');
                        char *next_frame = strchr(gcode_symbol, '\n');
                        if (next_command > next_frame) {
                            gcode_symbol = next_frame;
                        } else if (next_command != 0) {
                            gcode_symbol = next_command;
                        } else {
                            state = STATE_END;
                            break;
                        }
                        state = STATE_COMMAND_GROUP;
                }
                break;
            case STATE_COMMAND_GROUP_G:
                group_number = (int) strtol(gcode_symbol, &gcode_symbol, 10);
                switch (group_number) {
                    case 0:
                        debugf("STATE_G00_RAPID\n");
                        state = STATE_COMMAND_GROUP;
                        break;
                    case 1:
                        debugf("STATE_G01_LINEAR\n");
                        state = STATE_COMMAND_GROUP;
                        break;
                    default:
                        debugf("STATE_COMMAND_GROUP_G: not supported %d\n", group_number);
                        state = STATE_COMMAND_GROUP;
                }
                break;
            case STATE_X:
                x = strtof(gcode_symbol, &gcode_symbol);
                debugf("STATE_X: %f\n", x);
                state = STATE_COMMAND_GROUP;
                break;
            case STATE_Y:
                y = strtof(gcode_symbol, &gcode_symbol);
                debugf("STATE_Y: %f\n", y);
                state = STATE_COMMAND_GROUP;
                break;
            case STATE_Z:
                z = strtof(gcode_symbol, &gcode_symbol);
                debugf("STATE_Z: %f\n", z);
                state = STATE_COMMAND_GROUP;
                break;
            case STATE_FEED:
                feed = strtof(gcode_symbol, &gcode_symbol);
                debugf("STATE_FEED: %f\n", feed);
                state = STATE_COMMAND_GROUP;
                break;
        }
        gcode_symbol++;
        if (*gcode_symbol == 0) {
            state = STATE_END;
        }
    }
}