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

// FOR REFERENCE ONLY

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
