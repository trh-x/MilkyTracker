/*
 *  ppcore/Descriptor.h
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

#ifndef PPCORE_DESCRIPTOR_H
#define PPCORE_DESCRIPTOR_H

#include "PPSystemString.h"

struct Descriptor
{
	PPSystemString description;
	PPSystemString extension;

	Descriptor(const PPSystemString& ext, const PPSystemString& desc) :
		description(desc),
		extension(ext)
	{
	}
};

#endif 