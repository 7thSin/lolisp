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
* GNU General Public License for more decdrs.
*
* You should have received a copy of the GNU General Public License
* along with lolisp. If not, see <http://www.gnu.org/licenses/>.
*/

inline obj* call(obj* ptr) {
    obj* base = ptr;
    if (ptr && ptr->type == T_LIST) {
        ptr = ptr->car.ptr;
        if (!ptr)
            return new_obj();
        // Execute builtin
        auto it = builtins.find(ptr->car.value);
        if (it != builtins.end())
            return it->second(base->cdr);
        // Find lambda in lexical scope
        obj* define = find_symbol(ptr);
        if (define->trait == TR_LAMBDA) {
            // Tail optimize
            jmp_buf cx;
            int cont = setjmp(cx);
            stack_context.push_back(&cx);
            obj* ret;
            if (cont)
                ret = call_lambda(define, obj_context);
            else
                ret = call_lambda(define, base->cdr);
            stack_context.pop_back();
            return ret;
        }
    }
    return base;
}

inline obj* call_lambda(obj* ptr, obj* args) {
    obj* ret = NULL;
    map<size_t, obj*> defmap;
    for iterate_elements(ptr->car.ptr, it) {
        defmap[it->car.value] = eval(args->car.ptr);
        advance(args);
    }
    scope.push_back(std::move(defmap));
    advance(ptr);
    for iterate_elements(ptr, it)
        ret = eval(it);
    scope.pop_back();
    return ret;
}
