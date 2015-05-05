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

inline void advance(obj*& ptr) {
    ptr = ptr->cdr;
}

inline void descend(obj*& ptr) {
    ptr = ptr->car.ptr;
}

#define iterate_elements(ls, it) \
    (obj* _base = ls, *it = _base->car.ptr; \
    _base->cdr && it;\
    advance(_base), it = _base->car.ptr)
    
#define iterate_list(ptr, it) \
    (obj* it = ptr; it->cdr; advance(it))
    
#define iterate_list_nil(ptr, it) \
    (obj* it = ptr; it; advance(it))

inline string make_stdstring(obj* ptr) {
    string str;
    for iterate_elements(ptr, it)
        str += (char)it->car.value;
    return str;
}

template <typename F, typename T> inline F recast(T& t) {
    return *reinterpret_cast<F*>(&t);
}

inline obj* cons(obj* head, obj* cdr) {
    obj* cell = nullptr;
    cell->car.ptr = head;
    cell->cdr = cdr;
    return cell;
}
