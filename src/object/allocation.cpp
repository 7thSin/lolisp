// Our global scope
map<size_t, obj*> defines;

// Allocated memory map
std::map<obj*, bool> mempool;

// Allocate new NIL object
// Must be used instead of the new operator.
inline obj* new_nil() {
    obj* o = new obj;
    mempool[o] = true;
    return o;
}

// Allocates object with a NIL tail
// Everything expects an object with non-null tail.
// Remember: lists terminate at NIL, not NULL.
inline obj* new_obj() {
    obj* o = new_nil();
    o->tail = new obj;
    mempool[o] = true;
    mempool[o->tail] = true;
    return o;
}

// Some sugar
inline obj* new_obj(unsigned type, unsigned trait = 0) {
    obj* o = new_obj();
    o->type = type;
    o->trait = trait;
    return o;
}
