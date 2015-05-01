namespace builtin {
#include "list.cpp"
#include "print.cpp"
#include "eval.cpp"
}

// Collisions are improbable, but may happen.
// Still better than PHP's strlen() hash function
map<size_t, fptr> builtins = {
    { crc64("+"), builtin::sum },
    { crc64("-"), builtin::sub },
    { crc64("*"), builtin::mult },
    { crc64("/"), builtin::div },
    { crc64("="), builtin::eql },
    { crc64("eq-trait"), builtin::eql_traits },
    { crc64("list"), builtin::list },
    { crc64("string"), builtin::stringify },
    { crc64("clear"), builtin::clear },
    { crc64("print"), builtin::print },
    { crc64("car"), builtin::car },
    { crc64("cdr"), builtin::cdr },
    { crc64("crc"), builtin::crc }, 
    { crc64("shell"), builtin::shell },
    { crc64("exit"), builtin::exit },
    { crc64("partial-sum-int"), builtin::partial_sum_int },
    { crc64("objdump"), builtin::objdump },
    { crc64("nobjdump"), builtin::objdump2 },
    { crc64("lambda"), builtin::lambda },
    { crc64("quote"), builtin::quote },
    { crc64("eval"), builtin::evalc },
    { crc64("symbolp"), builtin::symbolp },
    { crc64("atomp"), builtin::atomp },
    { crc64("listp"), builtin::listp },
    { crc64("defun"), builtin::defun },
    { crc64("define"), builtin::define },
    { crc64("compile-file"), builtin::compile_file },
    { crc64("set"), builtin::set },
    { crc64("defdump"), builtin::defdump },
    { crc64("gc-trigger"), builtin::gc_trigger },
    { crc64("length"), builtin::length },
    { crc64("format"), builtin::format },
};
