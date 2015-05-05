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

// There MUST be a better way
// Please let me know
// I expect the compiler to optimize this out anyway
// TODO: use libgmp or something
template <typename Ff>
struct Num {
    double value = 0.0;
    Ff operation;
    unsigned trait = TR_UINT;
    Num() : operation(Ff()) {}
    void apply(obj* v) {
        switch (v->trait) {
            case TR_UINT:
                value = operation(value, v->car.value);
                break;
            case TR_INT:
                value = operation(value, (long long)v->car.value);
                break;
            case TR_FLOAT:
                value = operation(value, recast<double>(v->car.value));
                break;
        }
        if (v->trait > trait)
            trait = v->trait;
    }
    void set(obj* o) {
        trait = o->trait;
        switch (trait) {
            case TR_INT:
                value = (double)(long long)o->car.value;
                break;
            case TR_UINT:
                value = (double)o->car.value;
                break;
            default:
                value = recast<double>(o->car.value);
        }
    }
    size_t get() {
        switch (trait) {
            case TR_UINT:
            case TR_INT:
                return (long long)value;
            default:
                return recast<size_t>(value);
        }
    }
};
