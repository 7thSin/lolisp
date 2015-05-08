/*
* main.cpp
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include <regex>
#include <functional>
#include <fcntl.h>
#include <unistd.h>
#include <csignal>

using std::stringstream;
using std::fstream;
using std::string;
using std::stoi;
using std::to_string;
using std::cout;
using std::endl;
using std::map;

bool interactive = true;
string initexpr = "(load \"src/lisp/stdlib.loli\")";
string initrc = "(cat (getenv \"HOME\") \"/.lolisprc.loli\")";

void die(const char* m) {
    std::cerr << m << endl;
    exit(1);
}

#include "proto.cpp"
#include "hash.cpp"
#include "object/include.h"
#include "print.cpp"
#include "parser/lisp_tree.cpp"
#include "debugger.cpp"
#include "signal.cpp"
#include "eval/eval.cpp"
#include "opts.cpp"
#include "readline.cpp"

int main(int argc, char* argv[]) {
    parse_opts(argc, argv);
    signals::init();
    add_define("*interactive*", T_NIL, TR_UINT, interactive);
    obj* initobj = lisp_tree(initexpr);
    for iterate_list(initobj, it)
        eval(it->car.ptr);
    initrc = "(load " + initrc + ")";
    initobj = lisp_tree(initrc);
    for iterate_list(initobj, it)
        eval(it->car.ptr);
    initrc.clear();
    initexpr.clear();
    gc_collect();
    if (interactive) {
        rl_basic_word_break_characters = " \t\n(";
        rl_attempted_completion_function = autocomplete_functions;
        const char* prompt = "λ) ";
        while (true) {
            char* line = readline(prompt);
            if (!line)
                break;
            string cmdline = line;
            if (!cmdline.length()) continue;
            add_history(cmdline.c_str());
            free(line);
            string cmd = "(print " + string(cmdline) + ")";
            obj* tree = lisp_tree(cmd);
            eval(tree->car.ptr);
            gc_collect();
        }
    }
}
