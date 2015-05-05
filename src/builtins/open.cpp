/*
* open.cpp
* This file is part of lolisp
*
* Copyright (C) 2015 - Rei <https://github.com/sovietspaceship>
*
* lolisp is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* lolisp is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with lolisp. If not, see <http://www.gnu.org/licenses/>.
*/

/*
  AUTHOR: https://github.com/serialexperiments <lain@lain.org.uk>
*/

// open a gap in gensokyo
obj* open(obj* ptr) {
	obj* fd = new_obj(T_ATOM, TR_UINT);
	string filename = make_stdstring(ptr->car.ptr);
	advance(ptr);
	ptr = eval(ptr->car.ptr);
	fd->car.value = ::open(filename.c_str(), ptr->car.value);
	
	return fd;
}
