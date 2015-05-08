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
        if (define->trait == TR_LAMBDA)
            return call_lambda(define, base->cdr);
    }
    return base;
}

inline obj* call_lambda(obj* ptr, obj* args) {
    obj* ret = NULL;
    map<size_t, obj*> defmap;
    scope.push_back(std::move(defmap));
    for iterate_elements(ptr->car.ptr, it) {
        scope.back()[it->car.value] = eval(args->car.ptr);
        advance(args);
    }
    advance(ptr);
    for iterate_elements(ptr, it)
        ret = eval(it);
    scope.pop_back();
    return ret;
}
