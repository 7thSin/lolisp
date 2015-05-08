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
        o = eval(eval(it->car.ptr));
    return o;
}

obj* compile_file(obj* ptr) {
    obj* fname = eval(ptr->car.ptr);
    if (fname->trait != TR_CHAR)
        return new_obj();

    string filename = make_stdstring(fname);
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
    cout << "Compiling... " << std::flush;
    obj* base = ::lisp_tree(src);
    cout << "done." << endl;
    return base;
}

obj* load(obj* ptr) {
    obj* data = compile_file(ptr);
    if (data->type == T_NIL)
        return data;
    obj* ret = NULL;
    for iterate_elements(data, it)
        ret = ::eval(it);
    return ret;
}

obj* read(obj* ptr) {
    string src;
    std::getline(std::cin, src, '\n');
    return lisp_tree(src)->car.ptr;
}

obj* if_b(obj* ptr) {
    if (!eval(ptr->car.ptr)->car.value)
        return new_obj();
    advance(ptr);
    obj* o = new_obj();
    for iterate_list(ptr, it)
        o = eval(eval(it->car.ptr));
    return o;
}

obj* while_b(obj* ptr) {
    obj* o = new_obj();
    obj* start = ptr;
    while (eval(ptr->car.ptr)->car.value) {
        for iterate_list(ptr, it)
            o = eval(eval(it->car.ptr));
        ptr = start;
    }
    return o;
}

obj* readlinef(obj* ptr) {
    obj* prompt = ptr->car.ptr;
    const char* promptstr = NULL;
    if (prompt && prompt->type == T_LIST)
        promptstr = make_stdstring(prompt).c_str();
    string src = ::readline(promptstr);
    return lisp_tree(src)->car.ptr;
}
