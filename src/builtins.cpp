/*
* builtins.cpp
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

namespace builtin {
    // It works nice, but it's too long.
    // TODO: type-indipendent integer representation
    // something like (not a floating point number):
    // struct Num {
    //    bool sign;
    //    unsigned exponent;
    //    unsigned radix;
    // }
    // uint has a non-zero radix, int zero exponent, double has every entry;
    // Just an idea.
    obj* sum(obj* ptr) {
        obj* result = new obj;
        size_t uintvalue = 0;
        long long intvalue = 0;
        double fvalue = 0;
        
        for(; ptr; ptr = ptr->tail) {
            switch (ptr->type) {
                case T_ATOM:
                    switch (ptr->trait) {
                        case TR_UINT:
                            uintvalue += ptr->get<size_t>();
                            break;
                        case TR_INT:
                            intvalue += ptr->get<long long>();
                            break;
                        case TR_FLOAT:
                            fvalue += ptr->get<double>();
                            break;
                    }
                    break;
                case T_LIST: {
                        obj* val = eval(ptr);
                        result->value += val->value;
                    }
                    break;
            }
        }
        
        if (fvalue) {
            result->trait = TR_FLOAT;
            result->set(fvalue + uintvalue + intvalue);
        }
        else if (intvalue) {
            result->trait = TR_INT;
            result->set(uintvalue + intvalue);
        }
        else {
            result->trait = TR_UINT;
            result->set(intvalue);
        }
        result->type = T_ATOM;
        return result;
    }
    // Read above
    obj* sub(obj* ptr) {
        obj* result = new obj;
        size_t uintvalue = 0;
        long long intvalue = 0;
        double fvalue = 0;
        bool first = false;
        
        for(; ptr; ptr = ptr->tail) {
            switch (ptr->type) {
                case T_ATOM:
                    switch (ptr->trait) {
                        case TR_UINT:
                            if (first)
                                uintvalue -= ptr->get<size_t>();
                            else {
                                uintvalue = ptr->get<size_t>();
                                first = true;   
                            }
                            break;
                        case TR_INT:
                            if (first)
                                intvalue -= ptr->get<long long>();
                            else {
                                intvalue = ptr->get<long long>();
                                first = true;   
                            }
                            break;
                        case TR_FLOAT:
                            if (first)
                                fvalue -= ptr->get<double>();
                            else {
                                fvalue = ptr->get<double>();
                                first = true;   
                            }
                            break;
                    }
                    break;
                case T_LIST: {
                        obj* val = eval(ptr);
                        result->value += val->value;
                    }
                    break;
            }
        }
        
        if (fvalue) {
            result->trait = TR_FLOAT;
            result->set(fvalue + uintvalue + intvalue);
        }
        else if (intvalue) {
            result->trait = TR_INT;
            result->set(uintvalue + intvalue);
        }
        else {
            result->trait = TR_UINT;
            result->set(intvalue);
        }
        result->type = T_ATOM;
        return result;
    }
    obj* clear(obj* ptr) {
        obj* lolwut = new obj;
        lolwut->type = T_ATOM;
        lolwut->trait = TR_UINT;
        int a = system("reset");
        lolwut->value = a;
        return lolwut;
    }
    obj* print(obj* ptr) {
        for (obj* sxpr = (obj*)ptr; sxpr->tail; sxpr = sxpr->tail) {
            obj* o = eval((obj*)sxpr);
            cout << exprtrace(o) << endl;
        }
        return ptr;
    }
    obj* list(obj* ptr) {
        obj* ls = new obj;
        obj* base = new obj;
        base->type = T_LIST;
        base->set(ls);
        for(; ptr->tail; ptr = ptr->tail) {
            ls->replace(eval(ptr));
            ls->tail = new obj;
            ls = ls->tail;
        }
        return base;
    }
    obj* stringify(obj* ptr) {
        obj* ls = new obj;
        obj* base = new obj;
        base->type = T_LIST;
        base->set(ls);
        for(; ptr->tail; ptr = ptr->tail) {
            ls->replace(eval(ptr));
            ls->trait = TR_STRING;
            ls->tail = new obj;
            ls = ls->tail;
        }
        return base;
    }
    obj* car(obj* ptr) {
        if (ptr->type != T_LIST)
            return new obj;
        obj* res = eval(ptr);
        obj* carl = new obj;
        carl->replace(res->get<obj*>());
        carl->tail = NULL;
        return carl;
    }
    obj* cdr(obj* ptr) {
        if (ptr->type != T_LIST)
            return new obj;
        obj* tail = ((obj*)eval(ptr)->value)->tail;
        obj* ls = new obj;
        ls->type = T_LIST;
        ls->trait = ptr->trait;
        ls->set(tail);
        return ls;
    }
    obj* partial_sum_int(obj* ptr) {
        obj* result = new obj;
        result->type = T_ATOM;
        result->trait = TR_INT;
        obj* base = new obj;
        base->set(result);
        base->type = T_LIST;
        ptr = eval(ptr);
        for (ptr = (obj*)ptr->value; ptr->tail; ptr = ptr->tail) {
            switch (ptr->type) {
                case T_ATOM:
                    switch (ptr->trait) {
                        case TR_UINT:
                        case TR_INT:
                            result->value += ptr->get<long long>();
                            break;
                        default: {
                            result->tail = new obj;
                            result = result->tail;
                            result->replace(ptr);
                            result->tail = new obj;
                            result = result->tail;
                            result->type = T_ATOM;
                            result->trait = TR_INT;
                        }
                    }
                    break;
                case T_LIST: {
                        obj* val = eval(ptr);
                        result->value += val->value;
                    }
                    break;
            }
        }
        return base;
    }
    obj* crc(obj* ptr) {
        obj* result = new obj;
        string str;
        for (ptr = (obj*)ptr->value; ptr->tail; ptr = ptr->tail)
            str += (char)ptr->get<size_t>();
        result->value = crc64(str);
        result->type = T_ATOM;
        result->trait = TR_UINT;
        return result;
    }
}
