/*
* define.cpp
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

obj* defdump(obj* ptr) {
    for (auto const& it : defines) {
        if (!it.second) continue;
        cout << symcache[(obj*)it.first] << endl;
        objdump(it.second, it.first, "defdump");
        cout << exprtrace(it.second) << endl;
    }
    return new_t();
}

obj* defun(obj* ptr) {
    size_t name = ptr->car.ptr->car.value;
    advance(ptr);
    ptr->trait = TR_LAMBDA;
    defines.insert({ name, ptr });
    return new_t();
}
obj* define(obj* ptr) {
    size_t name = ptr->car.ptr->car.value;
    ptr = eval(ptr->cdr->car.ptr);
    defines[name] = ptr;
    return new_t();
}
obj* lambda(obj* ptr) {
    if (ptr->type != T_LIST)
        return new_obj();
    ptr->trait = TR_LAMBDA;
    return ptr;
}
obj* defmacro(obj* ptr) {
    size_t name = ptr->car.ptr->car.value;
    advance(ptr);
    ptr->trait = TR_LAMBDA;
    macros.insert({ name, ptr });
    return new_t();
}
