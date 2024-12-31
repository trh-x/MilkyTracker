/*
 *  ppcore/BasicTypes.h
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

#ifndef PPCORE_BASICTYPES__H
#define PPCORE_BASICTYPES__H

typedef unsigned char    pp_uint8;
typedef signed char     pp_int8;
typedef unsigned short  pp_uint16;
typedef signed short    pp_int16;
typedef unsigned int    pp_uint32;
typedef signed int      pp_int32;

// Basic structures needed by Dictionary
struct PPPoint 
{
    pp_int32 x, y;
    
    PPPoint() :
        x(0), y(0)
    {
    }
    
    PPPoint(pp_int32 x, pp_int32 y) :
        x(x), y(y)
    {
    }
};

struct PPSize 
{
    pp_int32 width, height;
    
    PPSize() :
        width(0), height(0)
    {
    }
    
    PPSize(pp_int32 width, pp_int32 height) :
        width(width), height(height)
    {
    }
};

struct PPRect 
{
    PPPoint position;
    PPSize size;
    
    PPRect() 
    {
    }
    
    PPRect(const PPPoint& position, const PPSize& size) :
        position(position), size(size)
    {
    }
};

#endif 