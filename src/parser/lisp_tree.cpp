/*
* parser.cpp
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

#include "addobj.cpp"
#include "macro.cpp"

// Reads a string and generates a s-expr tree
obj* lisp_tree(const string& src, size_t& i) {
    const size_t len = src.length();
    string token;
    
    obj* base = new_list();
    obj* ptr = base;
    
    // Loop starting after (
    for (; i < len; i++) {
        switch (src[i]) {
            case '(':
                token.clear();
                ptr->car.ptr = lisp_tree(src, ++i);
                ptr->cdr = new_list();
                advance(ptr);
                break;
            case '\'': {
                token.clear();
                obj* quot = new_obj(T_ATOM, TR_SYMBOL);
                quot->car.value = crc64("quote");
                ptr->car.ptr = quot;
                ptr->cdr = lisp_tree(src, ++i);
                return base;
            }
            case '"':
                ptr->car.ptr = addstring(src, ++i);
                ptr->cdr = new_list();
                advance(ptr);
                token.clear();
                break;
            case ')':
                add_atom(ptr, token);
                base = macro_apply(base);
                return base;
            case ';':
                for (; i < len && src[i] != '\n'; i++);
            case '\n':
            case '\t':
            case ' ':
                add_atom(ptr, token);
                token.clear();
                break;
            default:
                token += src[i];
        }
    }
    add_atom(ptr, token);
    return base;
}

inline obj* lisp_tree(const string& src) {
    size_t i = 0;
    return lisp_tree(src, i);
}
