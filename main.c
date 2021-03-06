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
#include <string.h>
#include "debug.h" 
#include "fsm.h"

State state_e;

/*
 * 
 */
int main(int argc, char** argv) {

    debugf("G-CODE файл: %s\n===\n", argv[1]);
    gcodeFSM(argv[1]);

    return (EXIT_SUCCESS);
}

