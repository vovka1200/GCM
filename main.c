/*
 * Copyright (C) 2017 Vladimir Yavorskiy
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

/* 
 * File:   main.c
 * Author: vovka
 *
 * Created on 28 сентября 2017 г., 10:53
 */

#include <stdio.h>
#include <stdlib.h>

#define STATE_END 0
#define STATE_FRAME 1
#define STATE_COMMAND_GROUP 2 
#define STATE_COMMAND_GROUP_G 3 
#define STATE_G00_RAPID 10
#define STATE_G00_RAPID_X 11
#define STATE_G00_RAPID_Y 12
#define STATE_G00_RAPID_Z 13
#define STATE_G01_LINEAR 20
#define STATE_G01_LINEAR_X 21
#define STATE_G01_LINEAR_Y 22
#define STATE_G01_LINEAR_Z 23
#define STATE_G01_LINEAR_FEED 24

#define GCODE_GROUP_G 1
#define GCODE_GROUP_M 2

int state = STATE_FRAME;
char *digits;
char *digit;
double x;
double y;
double z;
double feed;

int readDigits(char *symbol) {
    if (*symbol >= '0' && *symbol <= '9' || *symbol == '.') {
        *digit = *symbol;
        digit++;
        return 0;
    } else {
        *digit = 0;
        digit = digits;
        if (*symbol == '\n') {
            symbol--;
        }
        return 1;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    printf("G-CODE файл: %s\n", argv[1]);
    char *gcode_symbol = argv[1];
    digits = malloc(10);
    digit = digits;
    while (state != STATE_END) {
        switch (state) {
            case STATE_FRAME:
                switch (*gcode_symbol) {
                    case '%':
                        printf("STATE_FIRST_FRAME\n");
                        break;
                    case '\n':
                        state = STATE_COMMAND_GROUP;
                        break;
                }
                break;
            case STATE_COMMAND_GROUP:
                printf("STATE_COMMAND_GROUP: %c\n", *gcode_symbol);
                switch (*gcode_symbol) {
                    case 'G':
                        state = STATE_COMMAND_GROUP_G;
                        break;
                }
                break;
            case STATE_COMMAND_GROUP_G:
                printf("STATE_COMMAND_GROUP_G: %c\n", *gcode_symbol);
                if (readDigits(gcode_symbol) == 1) {
                    int gcode_number = atoi(digits);
                    printf("STATE_COMMAND_GROUP_G: %d\n", gcode_number);
                    switch (gcode_number) {
                        case 0:
                            state = STATE_G00_RAPID;
                            break;
                        case 1:
                            state = STATE_G01_LINEAR;
                            break;
                    }
                }
                break;
            case STATE_G00_RAPID:
                switch (*gcode_symbol) {
                    case 'X':
                        state = STATE_G00_RAPID_X;
                        break;
                    case 'Y':
                        state = STATE_G00_RAPID_Y;
                        break;
                    case 'Z':
                        state = STATE_G00_RAPID_Z;
                        break;
                    default:
                        state = STATE_COMMAND_GROUP;
                }
                break;
            case STATE_G00_RAPID_X:
                if (readDigits(gcode_symbol) == 1) {
                    x = atof(digits);
                    printf("STATE_G00_LINEAR_X: %f\n", x);
                    state = STATE_G00_RAPID;
                }
                break;
            case STATE_G00_RAPID_Y:
                if (readDigits(gcode_symbol) == 1) {
                    y = atof(digits);
                    printf("STATE_G00_LINEAR_Y: %f\n", y);
                    state = STATE_G00_RAPID;
                }
                break;
            case STATE_G00_RAPID_Z:
                if (readDigits(gcode_symbol) == 1) {
                    z = atof(digits);
                    printf("STATE_G00_LINEAR_Z: %f\n", z);
                    state = STATE_G00_RAPID;
                }
                break;
            case STATE_G01_LINEAR:
                switch (*gcode_symbol) {
                    case 'X':
                        state = STATE_G01_LINEAR_X;
                        break;
                    case 'Y':
                        state = STATE_G01_LINEAR_Y;
                        break;
                    case 'Z':
                        state = STATE_G01_LINEAR_Z;
                        break;
                    case 'F':
                        state = STATE_G01_LINEAR_FEED;
                        break;
                    default:
                        state = STATE_COMMAND_GROUP;
                }
                break;

            case STATE_G01_LINEAR_X:
                if (readDigits(gcode_symbol) == 1) {
                    x = atof(digits);
                    printf("STATE_G01_LINEAR_X: %f\n", x);
                    state = STATE_G01_LINEAR;
                }
                break;
            case STATE_G01_LINEAR_Y:
                if (readDigits(gcode_symbol) == 1) {
                    y = atof(digits);
                    printf("STATE_G01_LINEAR_Y: %f\n", y);
                    state = STATE_G01_LINEAR;
                }
                break;
            case STATE_G01_LINEAR_Z:
                if (readDigits(gcode_symbol) == 1) {
                    z = atof(digits);
                    printf("STATE_G01_LINEAR_Z: %f\n", z);
                    state = STATE_G01_LINEAR;
                }
                break;
            case STATE_G01_LINEAR_FEED:
                if (readDigits(gcode_symbol) == 1) {
                    feed = atof(digits);
                    printf("STATE_G01_LINEAR_FEED: %f\n", feed);
                    state = STATE_G01_LINEAR;
                }
                break;
        }
        gcode_symbol++;
        if (*gcode_symbol == 0) {
            state = STATE_END;
        }
    }
    return (EXIT_SUCCESS);
}

