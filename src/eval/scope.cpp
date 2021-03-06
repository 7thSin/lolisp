/*
* scope.cpp
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

std::vector<jmp_buf*> stack_context;
obj* obj_context;

obj* find_symbol(obj* ptr) {
    for (auto it = scope.rbegin(); it != scope.rend(); it++) {
        auto val_it = it->find(ptr->car.value);
        if (val_it != it->end())
            return val_it->second;
    }
    return ptr;
}
