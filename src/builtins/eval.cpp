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

obj* let(obj* ptr) {
    obj* ret = new_obj();
    map<size_t, obj*> defmap;
    scope.push_back(std::move(defmap));
    for iterate_elements(ptr->car.ptr, it) {
        obj* value = eval(it->cdr->car.ptr);
        if (!value) value = new_obj();
        scope.back()[it->car.ptr->car.value] = value;
    }
    advance(ptr);
    for iterate_elements(ptr, it)
        ret = eval(it);
    scope.pop_back();
    return ret;
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

obj* cond(obj* ptr) {
    obj* o = new_obj();
    for iterate_elements(ptr, it) {
        o = if_b(it);
        if (o->car.value)
            break;
    }
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

obj* recur(obj* ptr) {
    obj* nptr = new_list();
    obj* base = nptr;
    for iterate_list(ptr, it) {
        nptr->car.ptr = eval(it->car.ptr);
        nptr->cdr = new_list();
        advance(nptr);
    }
    obj_context = base;
    scope.pop_back();
    longjmp(*stack_context.back(), 1);
    return new_obj();
}
