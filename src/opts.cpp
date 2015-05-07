/*
* opts.cpp
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
* GNU General Public License for more decdrs.
*
* You should have received a copy of the GNU General Public License
* along with lolisp. If not, see <http://www.gnu.org/licenses/>.
*/

// TODO: replace with proper parsing
// just a prototype for testing purposes

void parse_opts(int argc, char* argv[]) {
    if (!strcmp(argv[0], "lolispc"))
        interactive = false;
    for (int i = 1; i < argc; i++) {
        if (!argv[i][0]) continue;
        char* next = NULL;
        if (i+1 < argc)
            next = argv[i+1];
        if (argv[i][0] == '-')
            switch (argv[i][1]) {
                case 'c': // do not enter repl
                    interactive = false;
                    break;
                case 'i':
                    interactive = true;
                    break;
                case 'n': // replace initial command
                    if (next)
                        initexpr = next;
                    else
                        die("error: invalid argument for -n.");
                    break;
                case 'r': // rc file
                    if (next)
                        initrc = next;
                    else
                        die("error: invalid argument for -r.");
                    break;
                case 'e': // "evaluate": append to initial command
                    if (next)
                        initexpr += next;
                    else
                        die("error: invalid argument for -e.");
                    break;
                case 'f': // load file
                    if (next)
                        initexpr += string("(load ") + next + ")";
                    else
                        die("error: invalid argument for -f.");
                    break;
            }
    }
}
