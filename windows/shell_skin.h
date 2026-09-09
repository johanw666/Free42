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

#define HWK_UNKNOWN    0
#define HWK_A          1
#define HWK_B          2
#define HWK_C          3
#define HWK_D          4
#define HWK_E          5
#define HWK_F          6
#define HWK_G          7
#define HWK_H          8
#define HWK_I          9
#define HWK_J         10
#define HWK_K         11
#define HWK_L         12
#define HWK_M         13
#define HWK_N         14
#define HWK_O         15
#define HWK_P         16
#define HWK_Q         17
#define HWK_R         18
#define HWK_S         19
#define HWK_T         20
#define HWK_U         21
#define HWK_V         22
#define HWK_W         23
#define HWK_X         24
#define HWK_Y         25
#define HWK_Z         26
#define HWK_0         27
#define HWK_1         28
#define HWK_2         29
#define HWK_3         30
#define HWK_4         31
#define HWK_5         32
#define HWK_6         33
#define HWK_7         34
#define HWK_8         35
#define HWK_9         36
#define HWK_SPACE     37
#define HWK_TAB       38
#define HWK_ENTER     39
#define HWK_ESC       40
#define HWK_F1        41
#define HWK_F2        42
#define HWK_F3        43
#define HWK_F4        44
#define HWK_F5        45
#define HWK_F6        46
#define HWK_F7        47
#define HWK_F8        48
#define HWK_F9        49
#define HWK_F10       50
#define HWK_F11       51
#define HWK_F12       52
#define HWK_F13       53
#define HWK_F14       54
#define HWK_F15       55
#define HWK_F16       56
#define HWK_F17       57
#define HWK_F18       58
#define HWK_F19       59
#define HWK_F20       60
#define HWK_ADD       61
#define HWK_SUBTRACT  62
#define HWK_MULTIPLY  63
#define HWK_DIVIDE    64
#define HWK_EQUALS    65
#define HWK_GRAVE     66
#define HWK_LEFT_BR   67
#define HWK_RIGHT_BR  68
#define HWK_QUOTE     69
#define HWK_PERIOD    70
#define HWK_COMMA     71
#define HWK_SEMICOLON 72
#define HWK_BACKSLASH 73
#define HWK_BACKSPACE 74
#define HWK_CLEAR     75
#define HWK_INSERT    76
#define HWK_DELETE    77
#define HWK_HOME      78
#define HWK_END       79
#define HWK_PRIOR     80
#define HWK_NEXT      81
#define HWK_UP        82
#define HWK_DOWN      83
#define HWK_LEFT      84
#define HWK_RIGHT     85

int hwk_key(int virtKey, bool cshift_suppressed, bool *hwk_numpad);
const char *hwk_text(int key);

#define KEYMAP_MAX_MACRO_LENGTH 31
#define MAX_MATCH_QUALITY 26
struct keymap_entry {
    bool old_style;
    bool ctrl;
    bool alt;
    bool shift;
    bool numpad; // for old_style, this is 'extended'
    bool numlock;
    bool cshift;
    int keycode;
    unsigned char macro[KEYMAP_MAX_MACRO_LENGTH + 1];
    int match(int keycode, bool ctrl, bool alt, bool shift, bool numpad, bool numlock, bool cshift,
              int old_keycode, bool old_shift, bool old_extended);
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
unsigned char *skin_keymap_lookup(int keycode, bool ctrl, bool alt, bool shift,
                                  bool numpad, bool numlock, bool cshift,
                                  int old_keycode, bool old_shift, bool old_extended,
                                  int *quality);
void skin_invalidate_key(int key);
void skin_display_blitter(const char *bits, int bytesperline, int x, int y, int width, int height);
void skin_get_size(int *width, int *height);
void skin_set_window(HWND window);
void skin_set_window_size(int width, int height);
void skin_get_window_size(int *width, int *height);

#endif
