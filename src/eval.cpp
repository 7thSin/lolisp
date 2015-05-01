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

obj* eval(obj* ptr);

#include "builtins/include.h"

inline obj* call(obj* ptr);
inline obj* call_lambda(obj* ptr);

obj* eval(obj* ptr) {
    switch (ptr->type) {
        case T_ATOM:
            return ptr;
        case T_LIST:
            return call(ptr);
    }
    return new_obj();
}

inline obj* call(obj* ptr) {
    switch (ptr->type) {
        case T_LIST: {
            obj* base = ptr;
            ptr = ptr->data.ptr;
            fptr func = builtins[ptr->data.value];
            if (func) 
                return func(ptr->tail);
            switch (base->trait) {
                case TR_LAMBDA:
                    return call_lambda(ptr);
                default:
                    obj* val = defines[ptr->data.value];
                    if (val)
                        return eval(val);
                    else
                        return ptr;
            }
        }
        break;
        default:
            return ptr;
    }
    return new_nil();
}

inline obj* call_lambda(obj* ptr) {
    obj* ret = new_obj();
    objdump(ptr);
    unsigned id = ptr->data.value;
    if (!id)
        return ret;
    obj* define = defines[id];
    objdump(define);
    for (; define->tail; advance(define)) {
        ret = eval(define);
    }
    return ret;
}
