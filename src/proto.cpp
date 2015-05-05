struct obj;
obj* debugger(unsigned options, const char* message, obj* criminal);
obj* eval(obj*);
inline obj* call(obj* ptr);
inline obj* call_lambda(obj* ptr, obj* args);
