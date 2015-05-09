/*
* misc.cpp
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

obj* crc(obj* ptr) {
    obj* result = new_obj(T_ATOM, TR_UINT);
    while (!ptr->car.ptr->type != T_LIST)
        ptr->car.ptr = debugger(DBG_REPLACE, "crc: invalid argument. Expected list.", ptr->car.ptr);
    result->car.value = crc64(make_stdstring(ptr->car.ptr));
    return result;
}
