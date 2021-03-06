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

/* 
 * File:   fsm.h
 * Author: Владимир Яворский <vovka@krevedko.su>
 *
 * Created on 1 октября 2017 г., 9:32
 */

#ifndef FSM_H
#define FSM_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum {
        START,
        STOP,
        GCODE_COMMENT,
        GCODE_LINE_NUMBER,
        GCODE_COMMAND,
        GCODE_COMMAND_G,
        GCODE_X,
        GCODE_Y,
        GCODE_Z,
        GCODE_FEED
    } State;

    void gcodeFSM(char *);

#ifdef __cplusplus
}
#endif

#endif /* FSM_H */

