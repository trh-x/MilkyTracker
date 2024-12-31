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
typedef signed long long pp_int64;
typedef unsigned long long pp_uint64;

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
    
    PPSize(pp_int32 theWidth, pp_int32 theHeight) :
        width(theWidth), height(theHeight)
    {
    }

    bool operator==(const PPSize& source) const
    {
        return (width == source.width && height == source.height);
    }

    bool operator!=(const PPSize& source) const
    {
        return !(width == source.width && height == source.height);
    }

    bool match(pp_int32 w, pp_int32 h) const
    {
        return width == w && height == h;
    }
};

struct PPRect 
{
    pp_int32 x1, y1, x2, y2;
    
    PPRect() :
        x1(0), y1(0), x2(0), y2(0)
    {
    }
    
    PPRect(const PPPoint& position, const PPSize& size) :
        x1(position.x), y1(position.y),
        x2(position.x + size.width), y2(position.y + size.height)
    {
    }

    PPRect(pp_int32 x1, pp_int32 y1, pp_int32 x2, pp_int32 y2) :
        x1(x1), y1(y1), x2(x2), y2(y2)
    {
    }

    PPPoint getPosition() const { return PPPoint(x1, y1); }
    PPSize getSize() const { return PPSize(x2 - x1, y2 - y1); }
    pp_int32 width() const { return x2 - x1; }
    pp_int32 height() const { return y2 - y1; }

    void scale(pp_int32 factor)
    {
        x1 *= factor;
        y1 *= factor;
        x2 *= factor;
        y2 *= factor;
    }

    bool intersect(const PPRect& r) const
    {
        return !(x2 < r.x1 || x1 > r.x2 || y2 < r.y1 || y1 > r.y2);
    }
};

struct PPColor
{
    pp_uint8 r,g,b;
    
    PPColor() :
        r(0), g(0), b(0)
    {
    }
    
    PPColor(pp_uint8 r, pp_uint8 g, pp_uint8 b) :
        r(r), g(g), b(b)
    {
    }

    void set(pp_uint8 _r, pp_uint8 _g, pp_uint8 _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }

    void scaleFixed(pp_uint32 scale)
    {
        r = (pp_uint8)((scale * r) >> 16);
        g = (pp_uint8)((scale * g) >> 16);
        b = (pp_uint8)((scale * b) >> 16);
    }

    void scale(float factor)
    {
        r = (pp_uint8)(r * factor);
        g = (pp_uint8)(g * factor);
        b = (pp_uint8)(b * factor);
    }

    void scale(float rFactor, float gFactor, float bFactor)
    {
        r = (pp_uint8)(r * rFactor);
        g = (pp_uint8)(g * gFactor);
        b = (pp_uint8)(b * bFactor);
    }

    void clamp()
    {
        r = r > 255 ? 255 : r;
        g = g > 255 ? 255 : g;
        b = b > 255 ? 255 : b;
    }

    PPColor& operator+=(const PPColor& other)
    {
        r = (pp_uint8)((pp_uint32)r + other.r);
        g = (pp_uint8)((pp_uint32)g + other.g);
        b = (pp_uint8)((pp_uint32)b + other.b);
        return *this;
    }
};

#endif 