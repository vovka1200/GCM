/*
 * Copyright (C) 2017 vovka
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

#define DEBUG

#define STATE_END 0
#define STATE_INIT -1
#define STATE_COMMAND_GROUP -2
#define STATE_COMMAND_NUMBER -3
#define STATE_G00_RAPID 1
#define STATE_G01_LINEAR 2

#define GCODE_GROUP_G 1
#define GCODE_GROUP_M 2

/*
 * 
 */
int main(int argc, char** argv) {

#ifdef DEBUG
    printf("G-CODE файл: %s\n", argv[1]);
#endif
    char *gcode_symbol = argv[1];
    int state = STATE_INIT;
    int gcode_group = 0;
    while (state != STATE_END) {
        switch (state) {
            case STATE_INIT:
#ifdef DEBUG
                printf("STATE_INIT\n");
#endif
                state = STATE_COMMAND_GROUP;
            case STATE_COMMAND_GROUP:
#ifdef DEBUG          
                printf("STATE_COMMAND_GROUP\n");
#endif
                if (*gcode_symbol == 'G') {
                    gcode_group = GCODE_GROUP_G;
                } else if (*gcode_symbol == 'M') {
                    gcode_group = GCODE_GROUP_M;
                }
#ifdef DEBUG
                printf("gcode_group=%d\n", gcode_group);
#endif
                gcode_symbol++;
                if (*gcode_symbol == 0) {
                    state = STATE_END;
                } else {
                    state = STATE_COMMAND_NUMBER;
                }
                break;
            case STATE_COMMAND_NUMBER:
#ifdef DEBUG
                printf("STATE_COMMAND_NUMBER\n");
#endif
                char * digits[10];
                char * digit = *digits;
                while (1) {
                    *digit = *gcode_symbol;
                    digit++;
                    gcode_symbol++;
                    if (*gcode_symbol == 32) {
                        *digit = 0;
                        state = STATE_END;
                        break;
                    }
                    if (*gcode_symbol != 0) {
                        *digit = 0;
                        state = STATE_END;
                        break;
                    }
                }
#ifdef DEBUG
                printf("%d", atoi(digits));
#endif
                break;
        }

    }

    /*    while (*gcode_symbol != 0) {
            printf("%c", *gcode_symbol);
            gcode_symbol++;
        }
     */
    return (EXIT_SUCCESS);
}

