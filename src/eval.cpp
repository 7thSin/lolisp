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
inline obj* call_lambda(obj* ptr, obj* args);

obj* eval(obj* ptr) {
    switch (ptr->type) {
        case T_ATOM:
            switch (ptr->trait) {
                case TR_SYMBOL: {
                    obj* val = defines[ptr->data.value];
                    if (val) {
                        obj* o = new_nil();
                        o->replace(val);
                        o->tail = ptr->tail;
                        return o;
                    }
                    else
                        return ptr;
                    break;
                }
                default:
                    return ptr;
            }
            break;
        case T_LIST:
            return call(ptr);
    }
    return ptr;
}

inline obj* call(obj* ptr) {
    switch (ptr->type) {
        case T_LIST: {
            obj* base = ptr;
            ptr = ptr->data.ptr;
            fptr func = builtins[ptr->data.value];
            if (func) 
                return func(ptr->tail);
            size_t id = ptr->data.value;
            obj* define = defines[id];
            if (!define)
                return base;
            switch (define->trait) {
                case TR_LAMBDA:
                    return call_lambda(define, ptr->tail);
                default:
                    return base;
            }
        }
        break;
        default:
            return ptr;
    }
    return new_nil();
}

inline obj* call_lambda(obj* ptr, obj* args) {
    obj* ret = new_obj();
    obj* scope = ptr;
    std::vector<size_t> local;
    for (descend(scope); scope->tail; advance(scope)) {
        size_t symb = scope->data.value;
        obj* o = new_obj();
        o->replace(args);
        defines[symb] = o;
        local.push_back(symb);
        advance(args);
    }
    args->tail = new_nil();
    for (advance(ptr); ptr->tail; advance(ptr)) {
        ret = eval(ptr);
    }
    for (auto const& it : local)
        defines.erase(it);
    return ret;
}
