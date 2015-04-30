z/*
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
        obj* result = new_obj();
        size_t uintvalue = 0;
        long long intvalue = 0;
        double fvalue = 0;
        
        for(; ptr; ptr = ptr->tail) {
            switch (ptr->type) {
                case T_LIST: {
                    obj* v = eval(ptr);
                    ptr->type = v->type;
                    ptr->trait = v->trait;
                    ptr->value = v->value;
                }
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
            result->set(uintvalue);
        }
        result->type = T_ATOM;
        return result;
    }
    // Read above
    obj* sub(obj* ptr) {
        obj* result = new_obj();
        size_t uintvalue = 0;
        long long intvalue = 0;
        double fvalue = 0;
        bool first = false;
        
        for(; ptr; ptr = ptr->tail) {
            switch (ptr->type) {
                case T_LIST:{
                    obj* v = eval(ptr);
                    ptr->type = v->type;
                    ptr->trait = v->trait;
                    ptr->value = v->value;
                }
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
            result->set(uintvalue);
        }
        result->type = T_ATOM;
        return result;
    }
    obj* clear(obj* ptr) {
        obj* lolwut = new_obj();
        lolwut->type = T_ATOM;
        lolwut->trait = TR_UINT;
        int a = system("reset");
        lolwut->value = a;
        return lolwut;
    }
    obj* shell(obj* ptr) {
        obj* lolwut = new_obj();
        lolwut->type = T_ATOM;
        lolwut->trait = TR_UINT;
        string cmd;
        if (!ptr->value)
            cmd = "/bin/sh";
        else for (ptr = (obj*)ptr->value; ptr->tail; ptr = ptr->tail)
            cmd += (char)ptr->get<size_t>();
        
        int a = system(cmd.c_str());
        lolwut->value = a;
        return lolwut;
    }
    obj* exit(obj* ptr) {
        long long estatus = ptr->get<long long>();
        ::exit(estatus);
        return new_obj();
    }
    obj* print(obj* ptr) {
        for (obj* sxpr = (obj*)ptr; sxpr->tail; sxpr = sxpr->tail) {
            obj* o = eval((obj*)sxpr);
            cout << exprtrace(o) << endl;
        }
        return ptr;
    }
    obj* list(obj* ptr) {
        obj* ls = new_obj();
        obj* base = new_obj();
        base->type = T_LIST;
        base->set(ls);
        for(; ptr->tail; ptr = ptr->tail) {
            ls->replace(eval(ptr));
            ls->tail = new_obj();
            ls = ls->tail;
        }
        return base;
    }
    obj* stringify(obj* ptr) {
        obj* ls = new_obj();
        obj* base = new_obj();
        base->type = T_LIST;
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
        obj* carl = new_obj();
        carl->replace(res->get<obj*>());
        carl->tail = NULL;
        return carl;
    }
    obj* cdr(obj* ptr) {
        if (ptr->type != T_LIST)
            return new_obj();
        obj* tail = ((obj*)eval(ptr)->value)->tail;
        obj* ls = new_obj();
        ls->type = T_LIST;
        ls->trait = ptr->trait;
        ls->set(tail);
        return ls;
    }
    obj* partial_sum_int(obj* ptr) {
        obj* result = new_obj();
        result->type = T_ATOM;
        result->trait = TR_INT;
        obj* base = new_obj();
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
                        result->value += val->value;
                    }
                    break;
            }
        }
        return base;
    }
    obj* crc(obj* ptr) {
        obj* result = new_obj();
        string str;
        for (ptr = (obj*)ptr->value; ptr->tail; ptr = ptr->tail)
            str += (char)ptr->get<size_t>();
        result->value = crc64(str);
        result->type = T_ATOM;
        result->trait = TR_UINT;
        return result;
    }
    obj* lambda(obj* ptr) {
        if (ptr->type != T_LIST)
            return new_obj();
        ptr->trait = TR_LAMBDA;
        return ptr;
    }
    obj* evalc(obj* ptr) {
        obj* ret = new_obj();
        for (; ptr->tail; ptr = ptr->tail)
            ret = ::eval(ptr);
        return ret;
    }
    obj* defun(obj* ptr) {
        size_t name = ptr->value;
        ptr = ptr->tail;
        obj* def = new obj;
        def->replace(ptr);
        def->tail = ptr->tail;
        def = lambda(def);
        defines[name] = def;
        return def;
    }
    obj* define(obj* ptr) {
        size_t name = ptr->value;
        ptr = eval(ptr->tail);
        obj* def = new obj;
        def->replace(ptr);
        defines[name] = def;
        return ptr;
    }
    obj* set(obj* ptr) {
        obj* dest = new_obj();
        dest->replace(ptr);
        dest = eval(dest);
        obj* src = new_obj();
        src->replace(ptr->tail);
        src = eval(src);
        dest->value = src->value;
        return dest;
    }
    obj* funcall(obj* ptr) {
        ptr->replace(::call(::eval(ptr)));
        return ptr;
    }
    obj* objdump(obj* ptr) {
        obj* eptr = eval(ptr);
        objdump(eptr, 0, "from REPL");
        return eptr;
    }
    obj* defdump(obj* ptr) {
        for (auto const& it : defines) {
            objdump(it.second, it.first, "defdump");
            cout << exprtrace(it.second) << endl;
        }
        return ptr;
    }
    obj* quote(obj* ptr) {
        return ptr;
    }
    obj* compile_file(obj* ptr) {     
<<<<<<< HEAD
        if (ptr->trait != TR_STRING)
            return new_obj();
=======
      if(ptr->trait != TR_STRING)
        return new_obj();
      
      string filename = "";
      stringstream reader;
      fstream fp;
      
      for (ptr = (obj*)ptr->value; ptr->tail; ptr = ptr->tail)
        filename += (char)ptr->get<size_t>();
>>>>>>> 5e579a80e732f9e526bc83a9718513eb5a06ae34

        string filename = "";
        stringstream reader;
        fstream fp;

<<<<<<< HEAD
        for (ptr = (obj*)ptr->value; ptr->tail; ptr = ptr->tail)
        filename += (char)ptr->get<size_t>();
=======
      if(!fp)
        return new_obj();
>>>>>>> 5e579a80e732f9e526bc83a9718513eb5a06ae34

        fp.open(filename, std::ios::in);
        if (!fp)
            return new_obj();

<<<<<<< HEAD
        reader << fp.rdbuf();
        fp.close();

        string src = reader.str();
        size_t i = 0;
        return ::lisp_tree(src, i);
    }
    obj* length(obj* ptr) {
	    ptr = (obj*)ptr->value;
	    ptr = eval(ptr);
	    obj* base = ptr;
	    size_t l;
	    for (l = 0; base->tail; base = base->tail)
		    l++;
	    obj* ret = new_obj();
	    ret->type = T_ATOM;
	    ret->trait = TR_UINT;
	    ret->value = l;
	    return ret;
    }
    obj* gc_trigger(obj* ptr) {
	    gc_collect();
	    return ptr;
=======
      fp.close();
      
      string src = reader.str();
      size_t i = 0;
      
      return ::lisp_tree(src, i);
    }
  
    obj* length(obj* ptr) {
      ptr = (obj*)ptr->value;
      ptr = eval(ptr);
      obj* base = ptr;
      size_t l;
      for (l = 0; base->tail; base = base->tail)
        l++;
      obj* ret = new_obj();
      ret->type = T_ATOM;
      ret->trait = TR_UINT;
      ret->value = l;
      return ret;
    }
    obj* gc_trigger(obj* ptr) {
      gc_collect();
      return ptr;
>>>>>>> 5e579a80e732f9e526bc83a9718513eb5a06ae34
    }
}
