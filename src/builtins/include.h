/*
* include.h
* This file is part of lolisp
*
* Copyright (C) 2015 - Rei <https://github.com/sovietspaceship>
*
* lolisp is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* lolisp is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with lolisp. If not, see <http://www.gnu.org/licenses/>.
*/

namespace builtin {
#include "list.cpp"
#include "print.cpp"
#include "eval.cpp"
#include "define.cpp"
#include "system.cpp"
#include "num.cpp"
#include "misc.cpp"
}

// Collisions are improbable, but may happen.
// Still better than PHP's strlen() hash function
map<size_t, fptr> builtins = {
    { crc64("+"), builtin::sum },
    { crc64("-"), builtin::sub },
    { crc64("*"), builtin::mult },
    { crc64("/"), builtin::div },
    { crc64("shell"), builtin::shell },
    { crc64("exit"), builtin::exit },
    { crc64("eval"), builtin::evalc },
    { crc64("objdump"), builtin::objdump },
    { crc64("quote"), builtin::quote },
    { crc64("defun"), builtin::defun },
    { crc64("define"), builtin::define },
    { crc64("compile-file"), builtin::compile_file },
    { crc64("defdump"), builtin::defdump },
    { crc64("length"), builtin::length },
    { crc64("format"), builtin::format },
    { crc64("car"), builtin::car },
    { crc64("cons"), builtin::cons },
    { crc64("cdr"), builtin::cdr },
    { crc64("crc"), builtin::crc },
    { crc64("print"), builtin::print },
    { crc64("list"), builtin::list },
};
