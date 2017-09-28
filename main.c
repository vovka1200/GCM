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

#define STATE_END 0
#define STATE_INIT -1
#define STATE_COMMAND_GROUP -2
#define STATE_COMMAND_NUMBER -3

/*
 * 
 */
int main(int argc, char** argv) {

    printf("G-CODE файл: %s\n", argv[1]);

    char *gcode_symbol = argv[1];
    int state = STATE_INIT;
    while (state != STATE_END) {
        switch (state) {
            case STATE_INIT:
                printf("INIT\n");
                state = STATE_COMMAND_GROUP;
                break;
            case STATE_COMMAND_GROUP:
                printf("GROUP\n");
                gcode_symbol++;
                if (*gcode_symbol == 0) {
                    state = STATE_END;
                }
                break;
            case STATE_COMMAND_NUMBER:
                printf("NUMBER\n");
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

