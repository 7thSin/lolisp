string make_stdstring(const obj* ptr) {
    string str;
    for (ptr = ptr->data.ptr; ptr->tail; ptr = ptr->tail)
        str += (char)ptr->data.value;
    return str;
}
