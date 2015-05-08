/*
* addobj.cpp
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

enum { RE_INT = 0, RE_UINT, RE_FLOAT, RE_HEX, RE_OCT, RE_BIN, RE_SYMBOL };

static const char* regex[] = {
    "^[+-]?[1-9][0-9]?*$",
    "^[0-9]*[uU]*$",
    "^[+-]?([0-9]+\\.([0-9]+)?|\\.[0-9]+)([eE][+-]?[0-9]+)?",
    "^0x[0-9a-fA-F]+",
    "^0[0-7]*",
    "^[0-9a-fA-F]+b",
    NULL,
};

void add_atom(obj*& base, const string& token) {
    if (!token.length()) return;
    base->car.ptr = new_obj(T_ATOM);
    obj* ptr = base->car.ptr;
    unsigned objtype;
    
    for (objtype = 0; regex[objtype]; objtype++)
        if (std::regex_match(token, std::regex(regex[objtype])))
            break;
    switch (objtype) {
        case RE_SYMBOL:
            ptr->trait = TR_SYMBOL;
            ptr->set(crc64(token));
            symcache[ptr->car.ptr] = token;
            break;
        case RE_INT:
            ptr->trait = TR_INT;
            ptr->set(std::stoll(token));
            break;
        case RE_BIN:
            ptr->set(std::stoull(token, NULL, 2));
            ptr->trait = TR_UINT;
            break;
        case RE_HEX:
            ptr->set(std::stoull(token, NULL, 16));
            ptr->trait = TR_UINT;
            break;
        case RE_OCT:
            ptr->set(std::stoull(token, NULL, 8));
            ptr->trait = TR_UINT;
            break;
        case RE_UINT:
            ptr->set(std::stoull(token));
            ptr->trait = TR_UINT;
            break;
        case RE_FLOAT:
            ptr->set(std::stod(token));
            ptr->trait = TR_FLOAT;
            break;
    }
    base->cdr = new_list();
    advance(base);
}

obj* addstring(const string& src, size_t& i) {
    obj* base = new_list();
    base->trait = TR_CHAR;
    obj* ptr = base;
    
    for (bool escape = false; i < src.length(); i++) {
        char buf = src[i];
        if (escape) {
            switch (buf) {
                case 'n':
                    buf = '\n';
                    break;
                case 't':
                    buf = '\t';
                    break;
            }
            escape = false;
        }
        else if (buf == '"') return base;
        else if (buf == '\\') {
            escape = true;
            continue;
        }
        ptr->car.ptr = new_obj(T_ATOM, TR_CHAR);
        obj* chars = ptr->car.ptr;
        chars->car.value = (size_t)buf;
        ptr->cdr = new_list();
        advance(ptr);
    }
    return base;
}
