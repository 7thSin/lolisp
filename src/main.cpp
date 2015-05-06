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

#include "proto.cpp"
#include "hash.cpp"
#include "object/include.h"
#include "print.cpp"
#include "parser/lisp_tree.cpp"
#include "debugger.cpp"
#include "signal.cpp"
#include "eval.cpp"

int main() {
    string initexpr = "(load \"src/lisp/stdlib.loli\")";
    size_t k = 0;
    eval(lisp_tree(initexpr, k));
    initexpr.clear();
    signals::init();
    const char* prompt = "λ) ";
    while (true) {
        char* cmdline = readline(prompt);
        add_history(cmdline);
        size_t i = 0;
        string cmd = "(print " + string(cmdline) + ")";
        free(cmdline);
        obj* tree = lisp_tree(cmd, i);
        tree = eval(tree);
        gc_collect();
    }
}
