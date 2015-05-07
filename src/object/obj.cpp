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

// Main data structure

struct obj {
    union {
        size_t       value  = 0;
        long long    ivalue;
        double       fvalue;
        obj*         ptr;
    } car;
    obj*             cdr   = NULL;
    unsigned short   type   = 0;
    unsigned short   trait  = 0;
    
    
    obj() {}
    obj(obj* head, obj* tail) {
        car.ptr = head;
        cdr = tail;
    };
    template <typename T> void set(T v) {
        car.value = *reinterpret_cast<size_t*>(&v);
    }
    template <typename T> T get() {
        return *reinterpret_cast<T*>(&car.value);
    }
    template <typename T> void convert() {
        car.value = static_cast<T>(car.value);
    }
    void replace(obj* o) {
        type = o->type;
        trait = o->trait;
        car.value = o->car.value;
    }
};

// Types

enum { 
    T_NIL = 0, 
    T_ATOM = 1,
    T_LIST = 2,
};

const char* types[] = {
    "NIL", 
    "ATOM", 
    "LIST", 
};

// Traits

enum {
    TR_UINT = 0,
    TR_INT = 1,
    TR_FLOAT = 2, 
    TR_SYMBOL = 3, 
    TR_CHAR = 4,
    TR_LAMBDA = 5,
};
const char* traits[] = {
    "UINT",
    "INT",
    "FLOAT", 
    "SYMBOL", 
    "CHAR", 
    "LAMBDA",
};

// Symbol cache
std::map<obj*, string> symcache;

void objdump(const obj* o, int line = 0, const char* label = NULL) {
    if (line && label)
        cout << "Object at " << line << ":" << label << endl;
    cout << "* address: " << o << endl;
    cout << "\t  type: " << types[o->type] << endl;
    cout << "\t trait: " << traits[o->trait] << endl;
    if (symcache[o->car.ptr].length())
        cout << "\t   car: " << symcache[o->car.ptr] << endl;
    else
        cout << "\t   car: " << o->car.ptr << endl;
    cout << "\t   cdr: " << o->cdr << endl;
}
