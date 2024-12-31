/*
 *  ppui/BasicTypes.h
 *
 *  Copyright 2009 Peter Barth
 *  Copyright 2024 Dale Whinham
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

#ifndef PPUI_BASICTYPES__H
#define PPUI_BASICTYPES__H

// Include core types
#include <ppcore/BasicTypes.h>

#if defined(WIN32) || defined(_WIN32_WCE) 
	#include <windows.h>
	#include <stdio.h>
	#define VK_ALT        VK_MENU
	#define __PPUI_WINDOWS__
#endif

#if !defined(__PPUI_WINDOWS__)
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "VirtualKeys.h"
	#include "PPSystemString_POSIX.h"
#endif

// UI-specific types and includes
#include "ScanCodes.h"

#endif
