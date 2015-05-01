/*
* exprtrace.cpp
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

string exprtrace(obj* base) {
    obj* ptr = base;
    string out;
    while (ptr) {
        switch (ptr->type) {
            case T_ATOM:
                switch (ptr->trait) {
                    case TR_STRING:
                        out += string("'") + (char)ptr->data.value + "'";
                        break;
                    case TR_FLOAT:
                        out += to_string(recast<double>(ptr->data.value));
                        break;
                    case TR_INT:
                        out += to_string(recast<signed long long>(ptr->data.value));
                        break;
                    case TR_UINT:
                        out += to_string(ptr->data.value);
                        break;
                    default:
                        out += to_string(ptr->data.value);
                }
                break;
            case T_LIST:
                if (ptr->data.ptr) {
                    out += '(';
                    out += exprtrace(ptr->data.ptr);
                    out.back() = ')';
                }
                else
                    out += "NIL";
                break;
            case T_NIL:
                out += "NIL";
                break;
            default:
                out += "?";
        }
        out += " ";
        ptr = ptr->tail;
    }
    return out;
}

string print(obj* base) {
    obj* ptr = base;
    string out;
    switch (ptr->type) {
        case T_ATOM:
            switch (ptr->trait) {
                case TR_STRING:
                    out += string("'") + (char)ptr->data.value + "'";
                    break;
                case TR_FLOAT:
                    out += to_string(recast<double>(ptr->data.value));
                    break;
                case TR_INT:
                    out += to_string(recast<signed long long>(ptr->data.value));
                    break;
                case TR_UINT:
                    out += to_string(ptr->data.value);
                    break;
                default:
                    out += to_string(ptr->data.value);
            }
            break;
        case T_LIST:
            if (ptr->data.ptr) {
                out += '(';
                out += exprtrace(ptr->data.ptr);
                out.back() = ')';
            }
            else
                out += "NIL";
            break;
        case T_NIL:
            out += "NIL";
            break;
        default:
            out += "?";
    }
    out += " ";
    ptr = ptr->tail;
    return out;
}
