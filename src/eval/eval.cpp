/*
* call.cpp
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

// Function pointer
typedef obj*(*fptr)(obj*);

#include "scope.cpp"
#include "../builtins/include.h"

obj* eval(obj* ptr) {
    switch (ptr->type) {
        case T_ATOM:
            switch (ptr->trait) {
                case TR_SYMBOL:
                    return find_symbol(ptr);
                default:
                    return ptr;
            }
        case T_LIST:
            return call(ptr);
    }
    return ptr;
}

#include "call.cpp"

