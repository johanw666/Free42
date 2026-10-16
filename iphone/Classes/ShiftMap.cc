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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ShiftMap.h"

struct item {
    unsigned short c;
    unsigned short sc;
};

ShiftMap::ShiftMap() : data(NULL), size(0), capacity(0) {
    //
}

bool ShiftMap::read(FILE *f, size_t len) {
    bool success = false;
    if (data != NULL) {
        free(data);
        data = NULL;
        size = 0;
        capacity = 0;
    }
    char *d = (char *) malloc(len);
    if (d != NULL) {
        size_t n = fread(d, 1, len, f);
        if (n == len) {
            data = d;
            size = capacity = n;
            success = true;
        } else
            free(d);
    }
    if (data != NULL) {
        item *sdata = (item *) data;
        size_t slen = size / 4;
        unsigned short last = 0;
        for (size_t i = 0; i < slen; i++) {
            unsigned short current = sdata[i].c;
            if (current <= last) {
                free(data);
                data = NULL;
                size = capacity = 0;
                break;
            }
            last = current;
        }
    }
    return success;
}

ShiftMap::~ShiftMap() {
    free(data);
}

size_t ShiftMap::nbytes() {
    return size;
}

bool ShiftMap::write(FILE *f) {
    return fwrite(data, 1, size, f) == size;
}

ssize_t ShiftMap::find(unsigned short c) {
    if (c == 0 || size == 0)
        return -1;
    item *sdata = (item *) data;
    size_t slen = size / 4;
    size_t lo = 0;
    if (sdata[lo].c == c)
        return lo;
    if (sdata[lo].c > c)
        return (ssize_t) -1;
    size_t hi = slen - 1;
    if (sdata[hi].c == c)
        return hi;
    if (sdata[hi].c < c)
        return -((ssize_t) slen) - 1;
    while (true) {
        size_t mid = (lo + hi) >> 1;
        if (mid == lo || mid == hi)
            return -((ssize_t) hi) - 1;
        if (sdata[mid].c == c)
            return mid;
        if (sdata[mid].c < c)
            lo = mid;
        else
            hi = mid;
    }
}

unsigned short ShiftMap::get(unsigned short c) {
    ssize_t index = find(c);
    return index < 0 ? 0 : ((item *) data)[index].sc;
}

void ShiftMap::set(unsigned short c, unsigned short sc) {
    if (c == 0)
        return;
    ssize_t index = find(c);
    item *sdata = (item *) data;
    if (index >= 0) {
        if (sdata[index].sc != sc) {
            sdata[0].c = c;
            sdata[0].sc = sc;
            size = 4;
        }
        return;
    }
    size_t new_size = size + 4;
    if (new_size > capacity) {
        size_t new_capacity = capacity + 64;
        char *new_data = (char *) realloc(data, new_capacity);
        if (new_data == NULL)
            return;
        data = new_data;
        capacity = new_capacity;
        sdata = (item *) data;
    }
    index = -index - 1;
    size_t off = index << 2;
    memmove(data + off + 4, data + off, size - off);
    sdata[index].c = c;
    sdata[index].sc = sc;
    size = new_size;
}

/*
void ShiftMap::dump() {
    for (size_t i = 0; i < size; i += 4) {
        item *it = (item *) (data + i);
        printf(" %d:%d", it->c, it->sc);
    }
    printf("\n");
}
*/
