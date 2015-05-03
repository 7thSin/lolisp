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
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with lolisp. If not, see <http://www.gnu.org/licenses/>.
*/

obj* print(obj* ptr) {
    obj* o = new_obj();
    for iterate_list(ptr, it) {
        o = eval(it->car.ptr);
        cout << ::print(o) << endl;
    }
    return o;
}

obj* format(obj* ptr) {
    obj* fmt = ptr->car.ptr;
    if (fmt->type != T_LIST)
        return new_obj();
    obj* arg = ptr->cdr;
    bool control = false;
    for iterate_elements(fmt, it) {
        obj* val = eval(arg->car.ptr);
        if (control) {
            switch (it->car.value) {
                case 'd':
                    cout << val->get<long long>();
                    advance(arg);
                    break;
                case 'c':
                    cout << val->get<char>();
                    advance(arg);
                    break;
                case 'u':
                    cout << val->car.value;
                    advance(arg);
                    break;
                case 'x':
                    cout << val->car.ptr;
                    advance(arg);
                    break;
                case 'f':
                    cout << val->get<double>();
                    advance(arg);
                    break;
                case '%':
                    cout << endl;
                    break;
                case 's':
                    cout << make_stdstring(val);
                    advance(arg);
                    break;
                default:
                    cout << (char)fmt->car.value;
            }
            control = false;
        }
        else if (it->car.value == '~')
            control = true;
        else {
            cout << (char)it->car.value;
        }
    }
    return new_obj();
}
