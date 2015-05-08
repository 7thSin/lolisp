/*
* readline.cpp
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

static char* strtocharp(const string& s) {
    char* r = new char[s.length() + 1];
    strcpy(r, s.data());
    return r;
}

static char* find_builtin(size_t& builtins_index, const char* text, size_t len) {
    auto builtins_it = builtins.begin();
    for (size_t k = 0; k < builtins_index; k++)
        std::advance(builtins_it, 1);
    while (builtins_it != builtins.end()) {
        builtins_index++;
        auto name_it = symcache.find((obj*)builtins_it->first);
        std::advance(builtins_it, 1);
        if (name_it == symcache.end())
            continue;
        if (name_it->second.length() < len)
            continue;
        if (name_it->second.substr(0, len) != string(text))
            continue;
        return strtocharp(name_it->second);
    }
    return NULL;
}

static char* find_defines(size_t& defines_index, const char* text, size_t len) {
    auto defines_it = scope[0].begin();
    for (size_t k = 0; k < defines_index; k++)
        std::advance(defines_it, 1);
    while (defines_it != scope[0].end()) {
        defines_index++;
        if (!defines_it->second) {
            std::advance(defines_it, 1);
            continue;
        }
        auto name_it = symcache.find((obj*)defines_it->first);
        std::advance(defines_it, 1);
        if (name_it == symcache.end())
            continue;
        if (name_it->second.length() < len)
            continue;
        if (name_it->second.substr(0, len) != string(text))
            continue;
        return strtocharp(name_it->second);
    }
    return NULL;
}

static char* command_generator(const char* text, int state) {
    static size_t len;
    static size_t defines_index;
    static size_t builtins_index;

    if (!state) {
        len = strlen(text);
        defines_index = 0;
        builtins_index = 0;
    }
    char* builtin_name = find_builtin(builtins_index, text, len);
    if (builtin_name)
        return builtin_name;
    char* defines_name = find_defines(defines_index, text, len);
    if (defines_name)
        return defines_name;
    
    return NULL;
}

char** autocomplete_functions(const char* text, int start, int end) {
    if (text[0] == '"')
        return NULL;
    return rl_completion_matches(text, command_generator);
}
