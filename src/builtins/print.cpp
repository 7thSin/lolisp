obj* print(obj* ptr) {
    for (; ptr->tail; ptr = ptr->tail) {
        obj* o = eval(ptr);
        cout << ::print(o) << endl;
    }
    return ptr;
}
