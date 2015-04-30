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
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include <regex>
using std::string;
using std::stoi;
using std::to_string;
using std::cout;
using std::endl;
using std::map;

void printerr(const string& src, unsigned long& i) {
    std::cout << src << std::endl;
    for (unsigned k = 0; k < i; k++)
    std::cout << ' ';
    std::cout << '^' << std::endl;
}

template <typename F> inline F recast(size_t& t) {
    return *reinterpret_cast<F*>(&t);
}

#include "hash.cpp"
#include "obj.cpp"
#include "addobj.cpp"
#include "parser.cpp"
#include "exprtrace.cpp"
#include "call.cpp"

int main() {
    const char* prompt = "λ) ";
    while (true) {
        char* cmdline = readline(prompt);
        add_history(cmdline);
        size_t i = 0;
        string initialcmd = "(print (eval " + string(cmdline) + "))";
        free(cmdline);
        obj* tree = lisp_tree(initialcmd, i);
        //cout << exprtrace(tree) << endl;
        eval((obj*)tree);
        freeall();
    }
}
