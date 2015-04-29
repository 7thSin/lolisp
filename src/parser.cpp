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
    obj* base = new obj;
    base->type = T_LIST;
    base->value = (size_t) new obj;
    obj* ptr = (obj*)base->value;
    string token;
    
    // Get to the beginning of the s-expression
    for (; src[i] != '(' && i < len; i++);
    
    // Loop starting after (
    for (i++; i < len; i++) {
        switch (src[i]) {
            case '(':
                token.clear();
                ptr->value = lisp_tree(src, i)->value;
                ptr->type = T_LIST;
                ptr->tail = new obj;
                ptr = ptr->tail;
                break;
            case '"':
                addstring(ptr, src, ++i);
                token.clear();
                break;
            case ')':
                addobj(ptr, token);
                base->tail = lisp_tree(src, i);
                break;
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
