/*
* eval.cpp
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

obj* evalc(obj* ptr) {
    obj* o = new_obj();
    for iterate_list(ptr, it)
        o = eval(it->car.ptr);
    return o;
}

obj* compile_file(obj* ptr) {
    if (ptr->car.ptr->trait != TR_CHAR)
        return new_obj();

    string filename = make_stdstring(ptr->car.ptr);
    stringstream reader;
    fstream fp;
    cout << "Loading " << filename << "... " << std::flush;
    fp.open(filename, std::ios::in);
    if (!fp.is_open()) {
        cout << "file not found." << endl;
        return new_obj();
    }
    cout << endl;
    while (reader << fp.rdbuf());
    fp.close();

    string src = reader.str();
    size_t i = 0;
    obj* o = new_obj();
    obj* base = o;
    base->type = T_LIST;
    cout << "Compiling... " << std::flush;
    while (i < src.length()) {
        obj* result = ::lisp_tree(src, i);
        if (result->type != T_NIL) {
            o->car.ptr = result;
            o->cdr = new_obj();
            advance(o);
        }
    }
    cout << "done." << endl;
    return base;
}
