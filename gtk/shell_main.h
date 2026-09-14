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

#ifndef SHELL_MAIN_H
#define SHELL_MAIN_H 1

#include <gtk/gtk.h>

#define FILENAMELEN 256

extern GtkWidget *calc_widget;
extern GtkWidget *mainwindow;
extern bool allow_paint;

struct state_type {
    int extras;
    int printerToTxtFile;
    int printerToGifFile;
    char printerTxtFileName[FILENAMELEN];
    char printerGifFileName[FILENAMELEN];
    int printerGifMaxLength;
    char mainWindowKnown, printWindowKnown, printWindowMapped;
    int mainWindowX, mainWindowY;
    int printWindowX, printWindowY, printWindowHeight;
    char skinName[FILENAMELEN];
    int singleInstance;
    char coreName[FILENAMELEN];
    bool matrix_singularmatrix;
    bool matrix_outofrange;
    bool auto_repeat;
    bool old_repaint;
    bool allow_big_stack;
    bool localized_copy_paste;
    int mainWindowWidth, mainWindowHeight;
};

extern state_type state;

extern char free42dirname[FILENAMELEN];

extern int ckey;
extern int skey;

extern int ann_updown;
extern int ann_shift;
extern int ann_print;
extern int ann_run;
extern int ann_battery;
extern int ann_g;
extern int ann_rad;

extern int menu_bar_height;

class keymap_entry;
void get_keymap(keymap_entry **map, int *length);


#endif
