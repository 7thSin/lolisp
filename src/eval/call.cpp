inline obj* call(obj* ptr) {
    obj* base = ptr;
    if (ptr && ptr->type == T_LIST) {
        ptr = ptr->car.ptr;
        // Execute builtin
        auto it = builtins.find(ptr->car.value);
        if (it != builtins.end())
            return it->second(base->cdr);
        // Find lambda in lexical scope
        obj* define = find_symbol(ptr);
        if (define->trait == TR_LAMBDA) {
            // Tail optimize
            jmp_buf cx;
            int cont = setjmp(cx);
            stack_context.push_back(&cx);
            obj* ret;
            if (cont)
                ret = call_lambda(define, obj_context);
            else
                ret = call_lambda(define, base->cdr);
            stack_context.pop_back();
            return ret;
        }
    }
    return base;
}

inline obj* call_lambda(obj* ptr, obj* args) {
    obj* ret = NULL;
    map<size_t, obj*> defmap;
    for iterate_elements(ptr->car.ptr, it) {
        defmap[it->car.value] = eval(args->car.ptr);
        advance(args);
    }
    scope.push_back(std::move(defmap));
    advance(ptr);
    for iterate_elements(ptr, it)
        ret = eval(it);
    scope.pop_back();
    return ret;
}
