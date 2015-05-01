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
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with lolisp. If not, see <http://www.gnu.org/licenses/>.
*/

// Reads a string and generates a s-expr tree
obj* lisp_tree(const string& src, size_t& i) {
    const size_t len = src.length();
    obj* base = new_obj();
    base->type = T_LIST;
    base->trait = TR_LAMBDA;
    base->data.ptr = new_obj();
    obj* ptr = base->data.ptr;
    string token;
    
    // Get to the beginning of the s-expression
    for (; src[i] != '(' && i < len; i++);
    
    // Loop starting after (
    for (i++; i < len; i++) {
        switch (src[i]) {
            case '(':
                token.clear();
                ptr->data.ptr = lisp_tree(src, i)->data.ptr;
                ptr->type = T_LIST;
                ptr->trait = TR_LAMBDA;
                ptr->tail = new_obj();
                ptr = ptr->tail;
                break;
            case '"':
                addstring(ptr, src, ++i);
                token.clear();
                break;
            case ')':
                addobj(ptr, token);
                return base;
            case '\n':
            case '\t':
            case ' ':
                addobj(ptr, token);
                token.clear();
                break;
            default:
                token += src[i];
        }
    }
    return base;
}
