/*
* allocation.cpp
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

// Our global scope
map<size_t, obj*> defines;

// Allocated memory map
std::map<obj*, bool> mempool;

// Symbol cache
std::map<obj*, string> symcache;

// Allocate new NIL object
// Must be used instead of the new operator.
inline obj* new_nil() {
    obj* o = new obj;
    mempool[o] = true;
    return o;
}

// Allocates object with a NIL tail
// Everything expects an object with non-null tail.
// Remember: lists terminate at NIL, not NULL.
inline obj* new_obj() {
    obj* o = new_nil();
    o->tail = new obj;
    mempool[o] = true;
    mempool[o->tail] = true;
    return o;
}

// Some sugar
inline obj* new_obj(unsigned type, unsigned trait = 0) {
    obj* o = new_obj();
    o->type = type;
    o->trait = trait;
    return o;
}
