/*
* num.cpp
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

// Generic sum
// Do not expect this to be fast
obj* sum(obj* ptr) {
    Num<std::plus<double>> res;
    for iterate_elements(ptr, it) {
        it = eval(it);
        switch (it->type) {
            case T_ATOM:
                res.apply(it);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->car.value = res.get();
    return result;
}

// Read above
obj* sub(obj* ptr) {
    Num<std::minus<double>> res;
    res.set(ptr->car.ptr);
    advance(ptr);
    for iterate_elements(ptr, it) {
        it = eval(it);
        switch (it->type) {
            case T_ATOM:
                res.apply(it);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->car.value = res.get();
    return result;
}
obj* mult(obj* ptr) {
    Num<std::multiplies<double>> res;
    res.value = 1.0;
    for iterate_elements(ptr, it) {
        it = eval(it);
        switch (it->type) {
            case T_ATOM:
                res.apply(it);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->car.value = res.get();
    return result;
}
obj* div(obj* ptr) {
    Num<std::divides<double>> res;
    res.set(ptr->car.ptr);
    advance(ptr);
    for iterate_elements(ptr, it) {
        it = eval(it);
        switch (it->type) {
            case T_ATOM:
                res.apply(it);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->car.value = res.get();
    return result;
}
