/*
* system.cpp
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

obj* exit(obj* ptr) {
    ::exit(ptr->car.ptr->car.value);
    return NULL;
}

obj* shell(obj* ptr) {
    obj* lolwut = new_obj(T_ATOM, TR_UINT);
    string cmd;
    if (!ptr->car.ptr)
        cmd = "/bin/sh";
    else
        cmd = make_stdstring(ptr->car.ptr);
    int a = system(cmd.c_str());
    lolwut->car.value = a;
    return lolwut;
}

obj* set_signal(obj* ptr) {
    size_t sig = eval(ptr->car.ptr)->car.value;
    advance(ptr);
    ::signals::set(sig, eval(ptr->car.ptr));
    return new_t();
}

obj* getenv(obj* ptr) {
    string str = make_stdstring(eval(ptr->car.ptr));
    str = ::getenv(str.c_str());
    size_t i = 0;
    return ::addstring(str, i);
}
