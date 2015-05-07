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

#include "builtins/include.h"

obj* eval(obj* ptr) {
    switch (ptr->type) {
        case T_ATOM:
            switch (ptr->trait) {
                case TR_SYMBOL: {
                    auto val_it = defines.find(ptr->car.value);
                    if (val_it != defines.end())
                        return val_it->second;
                    return ptr;
                }
                default:
                    return ptr;
            }
        case T_LIST:
            return call(ptr);
    }
    return ptr;
}

inline obj* call(obj* ptr) {
    switch (ptr->type) {
        case T_LIST: {
            obj* base = ptr;
            ptr = ptr->car.ptr;
            if (!ptr)
                return base;
            size_t id = ptr->car.value;
            auto func_it = builtins.find(id);
            if (func_it != builtins.end()) 
                return func_it->second(base->cdr);
            obj* define = defines[id];
            if (!define)
                return base;
            switch (define->trait) {
                case TR_LAMBDA:
                    return call_lambda(define, base->cdr);
                default:
                    return base;
            }
        }
        break;
        default:
            return ptr;
    }
}

inline obj* call_lambda(obj* ptr, obj* args) {
    obj* ret = new_obj();
    obj* scope = ptr;
    std::vector<size_t> local;
    scope = scope->car.ptr;
    for iterate_elements(scope, it) {
        size_t symb = it->car.value;
        defines[symb] = eval(args->car.ptr);
        local.push_back(symb);
        advance(args);
    }
    advance(ptr);
    for iterate_elements(ptr, it) {
        ret = eval(it);
    }
    for (auto const& it : local)
        defines.erase(it);
    return ret;
}
