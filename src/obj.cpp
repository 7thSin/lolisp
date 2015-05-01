/*
* obj.cpp
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

// Types
enum { T_NIL = 0, T_ATOM = 1, T_LIST = 2 };
const char* types[] = { "NIL", "ATOM", "LIST" };
// Traits
enum {
    TR_UINT = 0,
    TR_INT = 1,
    TR_FLOAT = 2, 
    TR_SYMBOL = 3, 
    TR_STRING = 4,
    TR_LAMBDA = 5,
};
const char* traits[] = { "INT", "UINT", "FLOAT", "SYMBOL", "STRING", "LAMBDA" };
// Main data structure
struct obj {
    unsigned char    type   = 0;
    unsigned char    trait  = 0;
    union {
        size_t       value  = 0;
        obj*         ptr;
    } data;
    obj*             tail   = NULL;
    
    template <typename T> void set(T v) {
        data.value = *reinterpret_cast<size_t*>(&v);
    }
    template <typename T> T get() {
        return *reinterpret_cast<T*>(&data.value);
    }
    template <typename T> void convert() {
        data.value = static_cast<T>(data.value);
    }
    void replace(obj* o) {
        type = o->type;
        trait = o->trait;
        data.value = o->data.value;
    }
};

void objdump(const obj* o, int line = 0, const char* label = "()") {
    cout << "Object at " << line << ":" << label << endl;
    cout << "* address: " << o << endl;
    cout << "\t  type: " << types[o->type] << endl;
    cout << "\t trait: " << traits[o->trait] << endl;
    cout << "\t value: " << o->data.ptr << endl;
    cout << "\t  tail: " << o->tail << endl;
}


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
                value = operation(value, v->data.value);
                break;
            case TR_INT:
                value = operation(value, (long long)v->data.value);
                break;
            case TR_FLOAT:
                value = operation(value, recast<double>(v->data.value));
                break;
        }
        if (v->trait > trait)
            trait = v->trait;
    }
    void set(obj* o) {
        trait = o->trait;
        switch (trait) {
            case TR_INT:
                value = (double)(long long)o->data.value;
                break;
            case TR_UINT:
                value = (double)o->data.value;
                break;
            default:
                value = recast<double>(o->data.value);
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
