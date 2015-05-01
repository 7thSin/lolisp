/*
* utils.cpp
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

#define iterate_eval(ptr) \
    (ptr = eval(ptr); ptr->tail; ptr = ptr->tail, ptr = eval(ptr))

inline string make_stdstring(const obj* ptr) {
    string str;
    for (ptr = ptr->data.ptr; ptr->tail; ptr = ptr->tail)
        str += (char)ptr->data.value;
    return str;
}

inline void advance(obj*& ptr) {
    ptr = ptr->tail;
}

inline void descend(obj*& ptr) {
    ptr = ptr->data.ptr;
}

template <typename F, typename T> inline F recast(T& t) {
    return *reinterpret_cast<F*>(&t);
}
