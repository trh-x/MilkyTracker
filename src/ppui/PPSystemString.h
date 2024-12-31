/*
 *  ppui/PPSystemString.h
 *
 *  Copyright 2023 
 *
 *  This file is part of Milkytracker.
 *
 *  Milkytracker is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Milkytracker is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Milkytracker.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PPUI_SYSTEMSTRING_H
#define PPUI_SYSTEMSTRING_H

#ifdef WIN32
#include "osinterface/win32/PPSystemString_WIN32.h"
#else
#include "osinterface/posix/PPSystemString_POSIX.h"
#endif

#endif 