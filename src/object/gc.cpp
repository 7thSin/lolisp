/*
* gc.cpp
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

// Mark and sweep garbage collection

void gc_sweep() {
    for (auto it = mempool.cbegin(); it != mempool.cend();) {
        if (it->second) {
            delete it->first;
            mempool.erase(it++);
        }
        else ++it;
    }
}

void gc_mark(obj* ptr) {
    for (; ptr; ptr = ptr->cdr) {
        switch (ptr->type) {
            case T_LIST:
                gc_mark(ptr->car.ptr);
            default:
                mempool[ptr] = false;
        }
    }
}

void gc_collect() {
    for (auto const& it : scope[0])
        gc_mark(it.second);
    for (auto const& it : macros)
        gc_mark(it.second);
    gc_sweep();
}
