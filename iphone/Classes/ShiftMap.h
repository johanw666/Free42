/*****************************************************************************
 * Free42 -- an HP-42S calculator simulator
 * Copyright (C) 2004-2026  Thomas Okken
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/.
 *****************************************************************************/

class ShiftMap {
    private:
        char *filename;
        char *data;
        size_t size, capacity;
    public:
        ShiftMap(const char *fn);
        ~ShiftMap();
        void write();
        ssize_t find(unsigned short c);
        unsigned short get(unsigned short c);
        void set(unsigned short c, unsigned short sc);
};
