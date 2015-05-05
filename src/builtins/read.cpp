/*
* close.cpp
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

obj* read(obj* ptr) {
	ptr = eval(ptr->car.ptr);
	int fd = ptr->car.value;
	advance(ptr);
	ptr = eval(ptr->car.ptr);
	size_t count = ptr->car.value;
	std::string data = "";
	data.reserve(count);
	::read(fd, &data[0], count);
	size_t i = 0;
	return ::add_string(data, i);
}
