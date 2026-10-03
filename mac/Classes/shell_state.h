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

#import <stdio.h>
#import "free42.h"

#define FILENAMELEN 256

struct state_type {
    char coreName[FILENAMELEN];
    char skinName[FILENAMELEN];
    char printerTxtFileName[FILENAMELEN];
    char printerGifFileName[FILENAMELEN];
    bool printerToTxtFile;
    bool printerToGifFile;
    int printerGifMaxLength;
    bool mainWindowKnown;
    int mainWindowX, mainWindowY, mainWindowWidth, mainWindowHeight;
    bool printWindowKnown, printWindowMapped;
    int printWindowX, printWindowY, printWindowHeight;
};

extern state_type state;

extern FILE *statefile;

extern bool keymap_obsolete;


void init_shell_state(int4 version);
bool read_shell_state();
bool write_shell_state();
