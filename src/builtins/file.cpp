/*
* list.cpp
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

// Contributed by: 
// https://github.com/serialexperiments <lain@lain.org.uk>
// open a gap in gensokyo
obj* file_open(obj* ptr) {
	obj* fd = new_obj(T_ATOM, TR_INT);
	string filename = make_stdstring(ptr->car.ptr);
	advance(ptr);
	ptr = eval(ptr->car.ptr);
	fd->car.value = ::open(filename.c_str(), ptr->car.value, S_IRUSR | S_IWUSR);
	return fd;
}

// Contributed by:
// https://github.com/serialexperiments <lain@lain.org.uk>
obj* file_write(obj* ptr) {
	obj* nbytes = new_obj(T_ATOM, TR_INT);
	obj* a1 = eval(ptr->car.ptr);
	int fd = a1->car.value;
	advance(ptr);
	string data = make_stdstring(ptr->car.ptr);
	nbytes->car.value = ::write(fd, data.data(), data.length());
	return nbytes;
}

// Contributed by:
// https://github.com/serialexperiments <lain@lain.org.uk>
obj* file_read(obj* ptr) {
	obj* a1 = eval(ptr->car.ptr);
	int fd = a1->car.value;
	advance(ptr);
	obj* a2 = eval(ptr->car.ptr);
	size_t count = a2->car.value;
	std::string sbuf;
	sbuf.resize(count);
	ssize_t stfu = ::read(fd, &sbuf[0], count);
	stfu = stfu;
	size_t i = 0;
	return ::addstring(sbuf, i);
}

// Contributed by: 
// https://github.com/serialexperiments <lain@lain.org.uk>
// Close the world. txEn eht nepO
obj* file_close(obj* ptr) {
	obj* status = new_obj(T_ATOM, TR_INT);
	ptr = eval(ptr->car.ptr);
	int fd = ptr->car.value;

	status->car.value = ::close(fd);
	
	return status;
}
