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

	PPPoint(pp_int32 theX, pp_int32 theY) :
		x(theX), y(theY)
	{}
	
	PPPoint() 
	{}
};

struct PPSize
{
	pp_int32 width, height;

	PPSize(pp_int32 theWidth, pp_int32 theHeight) :
		width(theWidth), height(theHeight)
	{}
	
	PPSize() 
	{}

	bool operator==(const PPSize& source) const
	{
		return (width == source.width && height == source.height);
	}
	
	bool operator!=(const PPSize& source) const
	{
		return !(width == source.width && height == source.height);
	}
	
	bool match(pp_int32 width, pp_int32 height) const
	{
		return (this->width == width && this->height == height);
	}
};

struct PPRect
{
	pp_int32 x1, y1, x2, y2;

	PPRect(pp_int32 px1, pp_int32 py1, pp_int32 px2, pp_int32 py2) :
		x1(px1), y1(py1), x2(px2), y2(py2)
	{}

	PPRect()
	{}

	pp_int32 width() const { return x2-x1; }
	pp_int32 height() const { return y2-y1; }
	
	void scale(pp_int32 scaleFactor)
	{
		x1 *= scaleFactor;
		y1 *= scaleFactor;
		x2 *= scaleFactor;
		y2 *= scaleFactor;
	}
	
	bool intersect(const PPRect& rc) const
	{
		pp_int32 left1, left2;
		pp_int32 right1, right2;
		pp_int32 top1, top2;
		pp_int32 bottom1, bottom2;
		
		left1 = this->x1;
		left2 = rc.x1;
		right1 = this->x1 + this->width();
		right2 = rc.x1 + rc.width();
		top1 = this->y1;
		top2 = rc.y1;
		bottom1 = this->y1 + this->height();
		bottom2 = rc.y1 + rc.height();
		
		if (bottom1 < top2) return false;
		if (top1 > bottom2) return false;
		
		if (right1 < left2) return false;
		if (left1 > right2) return false;
		
		return true;
	} 
	
};

struct PPColor
{
	pp_int32 r,g,b;

	PPColor(pp_int32 red, pp_int32 green, pp_int32 blue) :
		r(red), g(green), b(blue)
	{}

	PPColor() :
		r(), g(), b()
	{}
	
	void validate()
	{
		if (r > 255) r = 255;
		if (g > 255) g = 255;
		if (b > 255) b = 255;
	}

	void scale(float f) 
	{
		r = (pp_int32)((float)r*f);
		g = (pp_int32)((float)g*f);
		b = (pp_int32)((float)b*f);
		validate();
	}

	void scale(float fr, float fg, float fb) 
	{
		r = (pp_int32)((float)r*fr);
		g = (pp_int32)((float)g*fg);
		b = (pp_int32)((float)b*fb);
		validate();
	}

	void scaleFixed(pp_int32 f) 
	{
		r = (r*f)>>16;
		g = (g*f)>>16;
		b = (b*f)>>16;
		validate();
	}
	
	void interpolateFixed(const PPColor& col, pp_int32 f)
	{
		r = (f*r + col.r*(65536-f)) >> 16;
		g = (f*g + col.g*(65536-f)) >> 16;
		b = (f*b + col.b*(65536-f)) >> 16;
		validate();
	}

	PPColor invert() const
	{
		PPColor c(255-r, 255-g, 255-b);
		return c;
	}

	void set(pp_int32 red, pp_int32 green, pp_int32 blue)
	{
		r = red; g = green; b = blue;
	}
	
	void clamp()
	{
		if (r < 0) r = 0;
		if (g < 0) g = 0;
		if (b < 0) b = 0;

		validate();
	}

	void operator+=(const PPColor& source)
	{
		r+=source.r;
		g+=source.g;
		b+=source.b;
		validate();
	}
	
	bool operator==(const PPColor& source) const
	{
		return (r == source.r && g == source.g && b == source.b);
	}
	
	bool operator!=(const PPColor& source) const
	{
		return !(r == source.r && g == source.g && b == source.b);
	}
};

#endif 