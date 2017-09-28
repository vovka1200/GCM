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
 * Author: Vladimir Yavorskiy <vovka@krevedko.su>
 *
 * Created on 28 сентября 2017 г., 10:53
 */

#include <stdio.h>
#include <stdlib.h> 

#define DEBUG
 
#ifdef DEBUG
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
#define debugf(s,d) {Serial.print(s); Serial.println(d,DEC);}
#else
#define debugf(...) printf(__VA_ARGS__);
#endif
#else
#define debugf(...)
#endif
 
int state = STATE_FRAME;
char *gcode_symbol;
char *digits;
char *digit;
double x;
double y;
double z;
double feed;

int readDigits() {
    if (*gcode_symbol >= '0' && *gcode_symbol <= '9' || *gcode_symbol == '.') {
        *digit = *gcode_symbol;
        digit++;
        return 0;
    } else {
        *digit = 0;
        digit = digits;
        if (*gcode_symbol == '\n') {
            gcode_symbol--;
        }
        return 1;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    debugf("G-CODE файл: %s\n", argv[1]);
    gcode_symbol = argv[1];
    digits = malloc(10);
    digit = digits;
    while (state != STATE_END) {
        switch (state) {
            case STATE_FRAME:
                switch (*gcode_symbol) {
                    case '%':
                        debugf("STATE_FIRST_FRAME\n");
                        break;
                    case '\n':
                        state = STATE_COMMAND_GROUP;
                        break;
                }
                break;
            case STATE_COMMAND_GROUP:
                switch (*gcode_symbol) {
                    case 'G':
                        state = STATE_COMMAND_GROUP_G;
                        break;
                }
                break;
            case STATE_COMMAND_GROUP_G:
                if (readDigits() == 1) {
                    int gcode_number = atoi(digits);
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
                if (readDigits() == 1) {
                    x = atof(digits);
                    debugf("STATE_G00_LINEAR_X: %f\n", x);
                    state = STATE_G00_RAPID;
                }
                break;
            case STATE_G00_RAPID_Y:
                if (readDigits() == 1) {
                    y = atof(digits);
                    debugf("STATE_G00_LINEAR_Y: %f\n", y);
                    state = STATE_G00_RAPID;
                }
                break;
            case STATE_G00_RAPID_Z:
                if (readDigits() == 1) {
                    z = atof(digits);
                    debugf("STATE_G00_LINEAR_Z: %f\n", z);
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
                if (readDigits() == 1) {
                    x = atof(digits);
                    debugf("STATE_G01_LINEAR_X: %f\n", x);
                    state = STATE_G01_LINEAR;
                }
                break;
            case STATE_G01_LINEAR_Y:
                if (readDigits() == 1) {
                    y = atof(digits);
                    debugf("STATE_G01_LINEAR_Y: %f\n", y);
                    state = STATE_G01_LINEAR;
                }
                break;
            case STATE_G01_LINEAR_Z:
                if (readDigits() == 1) {
                    z = atof(digits);
                    debugf("STATE_G01_LINEAR_Z: %f\n", z);
                    state = STATE_G01_LINEAR;
                }
                break;
            case STATE_G01_LINEAR_FEED:
                if (readDigits() == 1) {
                    feed = atof(digits);
                    debugf("STATE_G01_LINEAR_FEED: %f\n", feed);
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

