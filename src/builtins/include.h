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
#include "file.cpp"
}

// Collisions are improbable, but may happen.
// Still better than PHP's strlen() hash function
map<size_t, fptr> builtins = {
    { new_symbol("+"), builtin::sum },
    { new_symbol("-"), builtin::sub },
    { new_symbol("*"), builtin::mult },
    { new_symbol("/"), builtin::div },
    { new_symbol("shell"), builtin::shell },
    { new_symbol("lambda"), builtin::lambda },
    { new_symbol("exit"), builtin::exit },
    { new_symbol("eval"), builtin::evalc },
    { new_symbol("objdump"), builtin::objdump },
    { new_symbol("quote"), builtin::quote },
    { new_symbol("defun"), builtin::defun },
    { new_symbol("defmacro"), builtin::defmacro },
    { new_symbol("define"), builtin::define },
    { new_symbol("compile-file"), builtin::compile_file },
    { new_symbol("length"), builtin::length },
    { new_symbol("format"), builtin::format },
    { new_symbol("car"), builtin::car },
    { new_symbol("cons"), builtin::cons },
    { new_symbol("cdr"), builtin::cdr },
    { new_symbol("crc"), builtin::crc },
    { new_symbol("print"), builtin::print },
    { new_symbol("list"), builtin::list },
    { new_symbol("file-open"), builtin::file_open },
    { new_symbol("file-close"), builtin::file_close },
    { new_symbol("file-read"), builtin::file_read },
    { new_symbol("file-write"), builtin::file_write },
    { new_symbol("read"), builtin::read },
    { new_symbol("readline"), builtin::readlinef },
    { new_symbol("set-signal"), builtin::set_signal },
    { new_symbol("set-trait"), builtin::set_trait },
    { new_symbol("funcall"), builtin::funcall },
    { new_symbol("apply"), builtin::apply },
    { new_symbol("let"), builtin::let },
    { new_symbol("load"), builtin::load },
    { new_symbol("map"), builtin::mapf },
    { new_symbol("while"), builtin::while_b },
    { new_symbol("if"), builtin::if_b },
    { new_symbol("cat"), builtin::cat },
    { new_symbol("gc-size"), builtin::gc_size },
    { new_symbol("getenv"), builtin::getenv },
    { new_symbol("recur"), builtin::recur },
    { new_symbol("mod"), builtin::mod },
    { new_symbol("or"), builtin::bit_or },
    { new_symbol("and"), builtin::bit_and },
    { new_symbol("xor"), builtin::bit_xor },
    { new_symbol("lshift"), builtin::bit_lshift },
    { new_symbol("rshift"), builtin::bit_rshift },
    { new_symbol("not"), builtin::bit_not },
};
