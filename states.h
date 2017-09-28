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
 * File:   states.h
 * Author: Владимир Яворский <vovka@krevedko.su>
 *
 * Created on 28 сентября 2017 г., 22:58
 */

#ifndef STATES_H
#define STATES_H

#ifdef __cplusplus
extern "C" {
#endif

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


#ifdef __cplusplus
}
#endif

#endif /* STATES_H */

