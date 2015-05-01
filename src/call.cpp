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

typedef obj*(*bfn)(obj*);

inline obj* call(obj* ptr);
inline obj* call_lambda(obj* ptr);

obj* eval(obj* ptr) {
    switch (ptr->type) {
        case T_ATOM:
            return ptr;
        case T_LIST:
            switch (ptr->trait) {
                case TR_LAMBDA:
                    return call(ptr);
                default:
                    return ptr;
            }
    }
    return new_obj();
}

#include "builtins.cpp"

// Collisions are improbable, but may happen.
// Still better than PHP's strlen() hash function
map<size_t, bfn> builtins = {
    { crc64("+"), builtin::sum },
    { crc64("-"), builtin::sub },
    { crc64("*"), builtin::mult },
    { crc64("/"), builtin::div },
    { crc64("="), builtin::eql },
    { crc64("eq-trait"), builtin::eql_traits },
    { crc64("list"), builtin::list },
    { crc64("string"), builtin::stringify },
    { crc64("clear"), builtin::clear },
    { crc64("print"), builtin::print },
    { crc64("car"), builtin::car },
    { crc64("cdr"), builtin::cdr },
    { crc64("crc"), builtin::crc }, 
    { crc64("shell"), builtin::shell },
    { crc64("exit"), builtin::exit },
    { crc64("partial-sum-int"), builtin::partial_sum_int },
    { crc64("objdump"), builtin::objdump },
    { crc64("nobjdump"), builtin::objdump2 },
    { crc64("lambda"), builtin::lambda },
    { crc64("quote"), builtin::quote },
    { crc64("eval"), builtin::evalc },
    { crc64("symbolp"), builtin::symbolp },
    { crc64("atomp"), builtin::atomp },
    { crc64("listp"), builtin::listp },
    { crc64("defun"), builtin::defun },
    { crc64("define"), builtin::define },
    { crc64("compile-file"), builtin::compile_file },
    { crc64("set"), builtin::set },
    { crc64("defdump"), builtin::defdump },
    { crc64("gc-trigger"), builtin::gc_trigger },
    { crc64("length"), builtin::length },
};

inline obj* call(obj* ptr) {
    switch (ptr->type) {
        case T_LIST: {
            obj* base = ptr;
            ptr = ptr->data.ptr;
            bfn func = builtins[ptr->data.value];
            if (!func) switch (base->trait) {
                case TR_LAMBDA:
                    return call_lambda(ptr);
                default:
                    obj* val = defines[ptr->data.value];
                    if (val)
                        return eval(val);
                    else
                        return new_obj();
            }
            return func(ptr->tail);
        }
        break;
        default:
            return ptr;
    }
    return new_obj();
}

inline obj* call_lambda(obj* ptr) {
    obj* ret = new_obj();
    obj* define = defines[ptr->data.value];
    for (; define->tail; define = define->tail) {
        ret = eval(define);
    }
    return ret;
}
