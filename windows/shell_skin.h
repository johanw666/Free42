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

#ifndef SHELL_SKIN_H
#define SHELL_SKIN_H 1

#include <windows.h>

void skin_load(wchar_t *skinname, const wchar_t *basedir, long *width, long *height);

struct SkinColor {
    unsigned char r, g, b, pad;
};

#define IMGTYPE_MONO 1
#define IMGTYPE_GRAY 2
#define IMGTYPE_COLORMAPPED 3
#define IMGTYPE_TRUECOLOR 4

#define KEYMAP_MAX_MACRO_LENGTH 31
#define MAX_MATCH_QUALITY 16
struct keymap_entry {
    bool old_style;
    bool ctrl;
    bool alt;
    bool shift;
    bool numpad; // for old_style, this is 'extended'
    bool numlock;
    bool cshift;
    int keycode; // if zero, look at keychar instead (new style only)
    int keychar;
    unsigned char macro[KEYMAP_MAX_MACRO_LENGTH + 1];
    int match(int keychar, int shifted_keychar, int keycode, bool ctrl, bool alt, bool shift,
              bool numpad, bool numlock, bool cshift, bool old_shift, bool old_extended);
};

keymap_entry *parse_keymap_entry(bool old_style, char *line, int lineno);

int skin_getchar();
void skin_rewind();
bool skin_init_image(int type, int ncolors, const SkinColor *colors,
                     int width, int height);
void skin_put_pixels(unsigned const char *data);
void skin_finish_image();

void skin_repaint(bool shortcuts);
void skin_invalidate_annunciator(int which);
void skin_find_key(int x, int y, bool cshift, int *skey, int *ckey);
int skin_find_skey(int ckey, bool cshift);
unsigned char *skin_find_macro(int ckey, int *type);
keymap_entry *skin_keymap_lookup(int keychar, int shifted_keychar, int keycode, bool ctrl, bool alt, bool shift,
                                 bool numpad, bool numlock, bool cshift, bool old_shift, bool old_extended, int *quality);
int skin_find_shifted_code(int code);
void skin_invalidate_key(int key);
void skin_display_blitter(const char *bits, int bytesperline, int x, int y, int width, int height);
void skin_get_size(int *width, int *height);
void skin_set_window(HWND window);
void skin_set_window_size(int width, int height);
void skin_get_window_size(int *width, int *height);

#endif
