/*
* call.cpp
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

enum { 
    DBG_TERM = 0,
    DBG_REPLACE = 1,
};

obj* debugger(unsigned options = DBG_TERM, const char* message = NULL, obj* criminal = NULL) {
    const char* prompt = NULL;
    if (criminal)
        objdump(criminal);
    switch (options) {
        case DBG_TERM:
            prompt = "λ Quit? ";
            break;
        case DBG_REPLACE:
            prompt = "λ Enter a new value: ";
            break;
    }
    if (message)
        cout << message << endl;
    char* cmdline = readline(prompt);
    add_history(cmdline);
    size_t i = 0;
    string initialcmd = "(print " + string(cmdline) + ")";
    free(cmdline);
    obj* tree = lisp_tree(initialcmd, i);
    rl_on_new_line();
    return eval(tree);
}
