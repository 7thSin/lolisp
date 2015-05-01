inline string make_stdstring(const obj* ptr) {
    string str;
    for (ptr = ptr->data.ptr; ptr->tail; ptr = ptr->tail)
        str += (char)ptr->data.value;
    return str;
}

inline void advance(obj*& ptr) {
    ptr = ptr->tail;
}

inline void descend(obj*& ptr) {
    ptr = ptr->data.ptr;
}

template <typename F, typename T> inline F recast(T& t) {
    return *reinterpret_cast<F*>(&t);
}
