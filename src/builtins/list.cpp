/*
* list.cpp
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

obj* objdump(obj* ptr) {
    obj* eptr = eval(ptr);
    objdump(eptr, 0, "from REPL");
    return eptr;
}
obj* objdump2(obj* ptr) {
    obj* eptr = ptr;
    objdump(eptr, 2, "from REPL");
    return eptr;
}
// Generic sum
// Do not expect this to be fast
obj* sum(obj* ptr) {
    Num<std::plus<double>> res;
    for iterate_eval(ptr) {
        switch (ptr->type) {
            case T_ATOM:
                res.apply(ptr);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->data.value = res.get();
    return result;
}
// Read above
obj* sub(obj* ptr) {
    Num<std::minus<double>> res;
    res.set(ptr);
    for iterate_eval(ptr) {
        switch (ptr->type) {
            case T_ATOM:
                res.apply(ptr);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->data.value = res.get();
    return result;
}
obj* mult(obj* ptr) {
    Num<std::multiplies<double>> res;
    res.value = 1.0;
    for iterate_eval(ptr) {
        switch (ptr->type) {
            case T_ATOM:
                res.apply(ptr);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->data.value = res.get();
    return result;
}
obj* div(obj* ptr) {
    Num<std::divides<double>> res;
    res.set(ptr);
    for iterate_eval(ptr) {
        switch (ptr->type) {
            case T_ATOM:
                res.apply(ptr);
        }
    }
    obj* result = new_obj(T_ATOM, res.trait);
    result->data.value = res.get();
    return result;
}
obj* eql(obj* ptr) {
    obj* result = new_obj();
    obj* last = ptr;
    for (ptr = ptr->tail; ptr; ptr = ptr->tail) {
        switch (ptr->type) {
            case T_LIST: {
                obj* v = eval(ptr);
                ptr->type = v->type;
                ptr->trait = v->trait;
                ptr->data.value = v->data.value;
            }
            case T_ATOM:
                if (last->data.value != ptr->data.value)
                    return result;
                if (last->type != ptr->type)
                    return result;
                if (last->trait != ptr->trait)
                    return result;
                last = ptr;
        }
    }
    result->trait = TR_UINT;
    result->data.value = 1;
    result->type = T_ATOM;
    return result;
}
obj* eql_traits(obj* ptr) {
    obj* result = new_obj();
    obj* last = ptr;
    for (ptr = ptr->tail; ptr; ptr = ptr->tail) {
        switch (ptr->type) {
            case T_LIST: {
                obj* v = eval(ptr);
                ptr->type = v->type;
                ptr->trait = v->trait;
                ptr->data.value = v->data.value;
            }
            case T_ATOM:
                if (last->trait != ptr->trait)
                    return result;
                last = ptr;
        }
    }
    result->trait = TR_UINT;
    result->data.value = 1;
    result->type = T_ATOM;
    return result;
}
obj* atomp(obj* ptr) {
    obj* result = new_obj();
    for (; ptr; ptr = ptr->tail) {
        switch (ptr->type) {
            case T_LIST: {
                obj* v = eval(ptr);
                ptr->type = v->type;
                ptr->trait = v->trait;
                ptr->data.value = v->data.value;
            }
            case T_ATOM:
                if (ptr->type != T_ATOM)
                    return result;
        }
    }
    result->trait = TR_UINT;
    result->data.value = 1;
    result->type = T_ATOM;
    return result;
}
obj* listp(obj* ptr) {
    obj* result = new_obj();
    for (; ptr; ptr = ptr->tail) {
        switch (ptr->type) {
            case T_LIST: {
                obj* v = eval(ptr);
                ptr->type = v->type;
                ptr->trait = v->trait;
                ptr->data.value = v->data.value;
            }
            case T_ATOM:
                if (ptr->type != T_LIST)
                    return result;
        }
    }
    result->trait = TR_UINT;
    result->data.value = 1;
    result->type = T_ATOM;
    return result;
}
obj* symbolp(obj* ptr) {
    obj* result = new_obj();
    for (; ptr; ptr = ptr->tail) {
        switch (ptr->type) {
            case T_LIST: {
                obj* v = eval(ptr);
                ptr->type = v->type;
                ptr->trait = v->trait;
                ptr->data.value = v->data.value;
            }
            case T_ATOM:
                if (ptr->type != T_ATOM &&
                    ptr->trait == TR_SYMBOL)
                    return result;
        }
    }
    result->trait = TR_UINT;
    result->data.value = 1;
    result->type = T_ATOM;
    return result;
}
obj* clear(obj* ptr) {
    obj* lolwut = new_obj(T_ATOM, TR_UINT);
    int a = system("reset");
    lolwut->data.value = a;
    return lolwut;
}
obj* shell(obj* ptr) {
    obj* lolwut = new_obj(T_ATOM, TR_UINT);
    string cmd;
    if (!ptr->data.value)
        cmd = "/bin/sh";
    else for (ptr = ptr->data.ptr; ptr->tail; ptr = ptr->tail)
        cmd += (char)ptr->get<size_t>();
    int a = system(cmd.c_str());
    lolwut->data.value = a;
    return lolwut;
}
obj* exit(obj* ptr) {
    long long estatus = ptr->get<long long>();
    ::exit(estatus);
    return new_obj();
}
obj* list(obj* ptr) {
    obj* ls = new_obj();
    obj* base = new_obj(T_LIST);
    base->set(ls);
    for(; ptr->tail; ptr = ptr->tail) {
        ls->replace(eval(ptr));
        ls->tail = new_nil();
        ls = ls->tail;
    }
    return base;
}
obj* stringify(obj* ptr) {
    obj* ls = new_obj();
    obj* base = new_obj(T_LIST);
    base->set(ls);
    for(; ptr->tail; ptr = ptr->tail) {
        ls->replace(eval(ptr));
        ls->trait = TR_STRING;
        ls->tail = new_obj();
        ls = ls->tail;
    }
    return base;
}
obj* car(obj* ptr) {
    if (ptr->type != T_LIST)
        return new_obj();
    obj* res = eval(ptr);
    return res->data.ptr;
}
obj* cdr(obj* ptr) {
    if (ptr->type != T_LIST)
        return new_obj();
    obj* rest = eval(ptr);
    descend(rest);
    obj* ls = new_obj(T_LIST);
    ls->set(rest->tail);
    return ls;
}
obj* partial_sum_int(obj* ptr) {
    obj* result = new_obj(T_ATOM, TR_INT);
    obj* base = new_obj(T_LIST);
    base->set(result);
    ptr = eval(ptr);
    for (ptr = ptr->data.ptr; ptr->tail; ptr = ptr->tail) {
        switch (ptr->type) {
            case T_ATOM:
                switch (ptr->trait) {
                    case TR_UINT:
                    case TR_INT:
                        result->data.value += ptr->get<long long>();
                        break;
                    default: {
                        result->tail = new_obj();
                        result = result->tail;
                        result->replace(ptr);
                        result->tail = new_obj();
                        result = result->tail;
                        result->type = T_ATOM;
                        result->trait = TR_INT;
                    }
                }
                break;
            case T_LIST: {
                    obj* val = eval(ptr);
                    result->data.value += val->data.value;
                }
                break;
        }
    }
    return base;
}
obj* crc(obj* ptr) {
    obj* result = new_obj(T_ATOM, TR_UINT);
    result->data.value = crc64(make_stdstring(ptr));
    return result;
}
obj* lambda(obj* ptr) {
    if (ptr->type != T_LIST)
        return new_nil();
    ptr->trait = TR_LAMBDA;
    return ptr;
}
obj* defun(obj* ptr) {
    size_t name = ptr->data.value;
    ptr = ptr->tail;
    obj* def = new obj;
    def->replace(ptr);
    def->tail = ptr->tail;
    def = lambda(def);
    defines[name] = def;
    return new_obj(T_ATOM);
}
obj* define(obj* ptr) {
    size_t name = ptr->data.value;
    ptr = eval(ptr->tail);
    defines[name] = ptr;
    return new_obj(T_ATOM);
}
obj* set(obj* ptr) {
    obj* dest = new_nil();
    dest->replace(ptr);
    dest = eval(dest);
    obj* src = new_nil();
    src->replace(ptr->tail);
    src = eval(src);
    dest->data.value = src->data.value;
    return dest;
}
obj* defdump(obj* ptr) {
    for (auto const& it : defines) {
        cout << symcache[(obj*)it.first] << endl;
        objdump(it.second, it.first, "defdump");
        cout << exprtrace(it.second) << endl;
    }
    return ptr;
}
obj* quote(obj* ptr) {
    return ptr;
}
obj* format(obj* ptr) {
    obj* fmt = ptr->data.ptr;
    obj* arg = ptr->tail;
    bool control = false;
    for (; fmt->tail; advance(fmt)) {
        if (control) {
            arg = eval(arg);
            switch (fmt->data.value) {
                case 'd':
                    cout << arg->get<long long>();
                    advance(arg);
                    break;
                case 'c':
                    cout << arg->get<char>();
                    advance(arg);
                    break;
                case 'u':
                    cout << arg->data.value;
                    advance(arg);
                    break;
                case 'x':
                    cout << arg->data.ptr;
                    advance(arg);
                    break;
                case 'f':
                    cout << arg->get<double>();
                    advance(arg);
                    break;
                case '%':
                    cout << endl;
                    break;
                case 's':
                    cout << make_stdstring(arg->data.ptr);
                    advance(arg);
                    break;
                default:
                    cout << (char)fmt->data.value;
            }
            control = false;
        }
        else if (fmt->data.value == '~')
            control = true;
        else {
            cout << (char)fmt->data.value;
        }
    }
    return new_obj();
}
obj* compile_file(obj* ptr) {     
    if(ptr->trait != TR_STRING)
        return new_obj();

    string filename = make_stdstring(ptr);
    stringstream reader;
    fstream fp;

    fp.open(filename, std::ios::in);
    if (!fp)
        return new_obj();
    while (reader << fp.rdbuf());
    fp.close();

    string src = reader.str();
    size_t i = 0;
    obj* o = new_obj();
    obj* base = o;
    while (i < src.length()) {
        obj* result = ::lisp_tree(src, i);
        if (result->data.ptr->type != T_NIL) {
            o->replace(result);
            o->tail = new_obj();
            o = o->tail;
        }
    }
    return base;
}
obj* length(obj* ptr) {
    ptr = ptr->data.ptr;
    ptr = eval(ptr);
    obj* base = ptr;
    size_t l;
    for (l = 0; base->tail; base = base->tail)
	    l++;
    obj* ret = new_obj(T_ATOM, TR_UINT);
    ret->data.value = l;
    return ret;
}
obj* gc_trigger(obj* ptr) {
    gc_collect();
    return ptr;
}

