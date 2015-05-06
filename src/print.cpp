/*
* print.cpp
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

// Prints a lisp tree

string print(obj* base) {
    obj* ptr = base;
    string out;
    switch (ptr->type) {
        case T_ATOM:
            switch (ptr->trait) {
                case TR_CHAR:
                    out += string("'") + (char)ptr->car.value + "'";
                    break;
                case TR_FLOAT:
                    out += to_string(recast<double>(ptr->car.value));
                    break;
                case TR_INT:
                    out += to_string(recast<signed long long>(ptr->car.value));
                    break;
                case TR_UINT:
                    out += to_string(ptr->car.value);
                    break;
                case TR_SYMBOL: {
                    auto sym_it = symcache.find(ptr->car.ptr);
                    if (sym_it == symcache.end())
                        out += "#S" + to_string(ptr->car.value);
                    else
                        out += sym_it->second;
                    break;
                }
                default:
                    out += to_string(ptr->car.value);
            }
            break;
        case T_LIST:
            if (ptr->car.ptr) {
                if (ptr->trait == TR_CHAR) {
                    out += '"';
                    out += make_stdstring(ptr);
                    out += '"';
                }
                else {
                    out += '(';
                    for iterate_elements(ptr, it)
                        out += print(it);
                    out.back() = ')';
                }
            }
            else
                out += "NIL";
            break;
        case T_NIL:
            if (ptr->car.value)
                out += "T";
            else
                out += "NIL";
            break;
        default:
            out += "?";
    }
    out += " ";
    return out;
}

// Rebuild the original source from an s-expression tree.
// Useful for debugging, but may have other uses, like
// to make a dump of the program state in form of source code.

string exprtrace(obj* base) {
    obj* ptr = base;
    string out;
    switch (ptr->type) {
        case T_ATOM:
            switch (ptr->trait) {
                case TR_CHAR:
                    out += string("'") + (char)ptr->car.value + "'";
                    break;
                case TR_FLOAT:
                    out += to_string(recast<double>(ptr->car.value));
                    break;
                case TR_INT:
                    out += to_string(recast<signed long long>(ptr->car.value));
                    break;
                case TR_UINT:
                    out += to_string(ptr->car.value);
                    break;
                case TR_SYMBOL: {
                    auto sym_it = symcache.find(ptr->car.ptr);
                    if (sym_it == symcache.end())
                        out += "#S" + to_string(ptr->car.value);
                    else
                        out += sym_it->second;
                    break;
                }
                default:
                    out += to_string(ptr->car.value);
            }
            break;
        case T_LIST:
            if (ptr->car.ptr) {
                out += '(';
                for iterate_elements(ptr, it)
                    out += exprtrace(it);
                out.back() = ')';
            }
            else
                out += "NIL";
            break;
        case T_NIL:
            if (ptr->car.value)
                out += "T";
            else
                out += "NIL";
            break;
        default:
            out += "?";
    }
    out += " ";
    return out;
}
