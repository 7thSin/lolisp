obj* evalc(obj* ptr) {
    obj* o = new_obj();
    ptr = eval(ptr);
    for (; ptr->tail; ptr = ptr->tail)
        o = eval(ptr);
    return o;
}
