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

#define FSM_STATE_END 0
#define FSM_STATE_COMMENT 1
#define FSM_STATE_COMMAND_GROUP 2 
#define FSM_STATE_COMMAND_GROUP_G 3 
#define FSM_STATE_LINE_NUMBER 4 
#define FSM_STATE_G00_RAPID 10
#define FSM_STATE_G28_HOME 11
#define FSM_STATE_X 100
#define FSM_STATE_Y 101
#define FSM_STATE_Z 102
#define FSM_STATE_FEED 103

    void gcodeFSM(char *);

#ifdef __cplusplus
}
#endif

#endif /* FSM_H */

