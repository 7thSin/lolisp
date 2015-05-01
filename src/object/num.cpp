// There MUST be a better way
// Please let me know
// I expect the compiler to optimize this out anyway
// TODO: use libgmp or something
template <typename Ff>
struct Num {
    double value = 0.0;
    Ff operation;
    unsigned trait = TR_UINT;
    Num() : operation(Ff()) {}
    void apply(obj* v) {
        switch (v->trait) {
            case TR_UINT:
                value = operation(value, v->data.value);
                break;
            case TR_INT:
                value = operation(value, (long long)v->data.value);
                break;
            case TR_FLOAT:
                value = operation(value, recast<double>(v->data.value));
                break;
        }
        if (v->trait > trait)
            trait = v->trait;
    }
    void set(obj* o) {
        trait = o->trait;
        switch (trait) {
            case TR_INT:
                value = (double)(long long)o->data.value;
                break;
            case TR_UINT:
                value = (double)o->data.value;
                break;
            default:
                value = recast<double>(o->data.value);
        }
    }
    size_t get() {
        switch (trait) {
            case TR_UINT:
            case TR_INT:
                return (long long)value;
            default:
                return recast<size_t>(value);
        }
    }
};
