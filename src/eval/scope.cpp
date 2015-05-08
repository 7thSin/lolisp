obj* find_symbol(obj* ptr) {
    for (auto it = scope.rbegin(); it != scope.rend(); it++) {
        auto val_it = it->find(ptr->car.value);
        if (val_it != it->end())
            return val_it->second;
    }
    return ptr;
}
