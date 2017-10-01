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
 * File:   debug.h
 * Author: Владимир Яворский <vovka@krevedko.su>
 *
 * Created on 1 октября 2017 г., 9:34
 */

#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
#define debugf(s,d) {Serial.print(s); Serial.println(d,DEC);}
#else
#define debugf(...) printf(__VA_ARGS__);
#endif
#else
#define debugf(...)
#endif


#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H */

