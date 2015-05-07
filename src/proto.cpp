struct obj;
obj* debugger(unsigned options, const char* message, obj* criminal);
string exprtrace(obj* ptr);
obj* eval(obj*);
inline obj* call(obj* ptr);
inline obj* call_lambda(obj* ptr, obj* args);
