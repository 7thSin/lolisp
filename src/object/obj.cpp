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
    TR_STRING = 4,
    TR_LAMBDA = 5,
};
const char* traits[] = { 
    "INT",
    "UINT", 
    "FLOAT", 
    "SYMBOL", 
    "STRING", 
    "LAMBDA",
};

void objdump(const obj* o, int line = 0, const char* label = "()") {
    cout << "Object at " << line << ":" << label << endl;
    cout << "* address: " << o << endl;
    cout << "\t  type: " << types[o->type] << endl;
    cout << "\t trait: " << traits[o->trait] << endl;
    cout << "\t value: " << o->data.ptr << endl;
    cout << "\t  tail: " << o->tail << endl;
}
