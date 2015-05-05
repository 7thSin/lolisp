/*
* list.cpp
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

obj* car(obj* v) {
    obj* arg = eval(v->car.ptr);
    while (arg->type != T_LIST)
        arg = debugger(DBG_REPLACE, "Invalid list.", arg);
    return arg->car.ptr;
}

obj* cdr(obj* v) {
    obj* arg = eval(v->car.ptr);
    if (arg->type != T_LIST)
        return new_obj();
    return arg->cdr;
}

obj* cons(obj* v) {
    obj* arg = eval(v->car.ptr);
    advance(v);
    obj* arg2 = eval(v->car.ptr);
    obj* cell = new_list();
    cell->car.ptr = arg;
    cell->cdr = arg2;
    return cell;
}

obj* list(obj* v) {
    obj* cp = new_list();
    obj* base = cp;
    for iterate_list(v, it) {
        cp->car.ptr = eval(it->car.ptr);
        cp->cdr = new_list();
        advance(cp);
    }
    return base;
}

obj* length(obj* ptr) {
    obj* ret = new_obj(T_ATOM, TR_UINT);
    for iterate_list(ptr, it)
        ret->car.value++;
    return ret;
}

obj* quote(obj* ptr) {
    return ptr;
}

obj* set_trait(obj* ptr) {
    obj* trait = ptr;
    advance(ptr);
    ptr->car.ptr->trait = trait->car.ptr->car.value;
    return ptr;
}

obj* objdump(obj* ptr) {
    obj* eptr = eval(ptr->car.ptr);
    objdump(eptr, 0, "from REPL");
    return eptr;
}