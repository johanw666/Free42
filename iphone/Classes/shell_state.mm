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

#import "shell_state.h"
#import "core_main.h"


#define SHELL_VERSION 16

state_type state;

ShiftMap shiftMap;

FILE *statefile = NULL;

bool keymap_obsolete = false;
extern bool off_enable_flag;


void init_shell_state(int version) {
    switch (version) {
        case -1:
            state.printerToTxtFile = 0;
            state.printerToGifFile = 0;
            state.printerTxtFileName[0] = 0;
            state.printerGifFileName[0] = 0;
            state.printerGifMaxLength = 256;
            state.skinName[0] = 0;
            /* fall through */
        case 0:
            /* fall through */
        case 1:
            state.alwaysOn = 0;
            /* fall through */
        case 2:
            state.keyClicks = 1;
            /* fall through */
        case 3:
            state.hapticFeedback = 0;
            /* fall through */
        case 4:
            strcpy(state.landscapeSkinName, "Landscape");
            state.orientationMode = 0;
            state.maintainSkinAspect[0] = 1;
            state.maintainSkinAspect[1] = 1;
            /* fall through */
        case 5:
            off_enable_flag = false;
            /* fall through */
        case 6:
            strcpy(state.coreName, "Untitled");
            /* fall through */
        case 7:
            core_settings.matrix_singularmatrix = false;
            core_settings.matrix_outofrange = false;
            core_settings.auto_repeat = true;
            /* fall through */
        case 8:
            core_settings.allow_big_stack = false;
            /* fall through */
        case 9:
            /* fall through */
        case 10:
            core_settings.localized_copy_paste = true;
            /* fall through */
        case 11:
            state.swipeDirectionMode = 0;
            /* fall through */
        case 12:
            /* fall through */
        case 13:
            state.popupAlphaKeyboard = 1;
            /* fall through */
        case 14:
            keymap_obsolete = true;
            /* fall through */
        case 15: {
            FILE *f = fopen("config/shiftmap", "r");
            if (f != NULL) {
                if (fseek(f, 0, SEEK_END) == 0) {
                    long pos = ftell(f);
                    if (pos > 0 && fseek(f, 0, SEEK_SET) == 0)
                        shiftMap.read(f, (size_t) pos);
                }
                fclose(f);
                remove("config/shiftmap");
            }
            /* fall through */
        }
        case 16:
            /* current version (SHELL_VERSION = 16),
             * so nothing to do here since everything
             * was initialized from the state file.
             */
            ;
    }
}

static bool state_read_byte(char *c) {
    int ch = fgetc(statefile);
    if (ch == EOF)
        return false;
    *c = ch;
    return true;
}

static bool state_read_bytes(void *buf, int n) {
    return fread(buf, 1, n, statefile) == n;
}

static bool state_read_bool(bool *b) {
    return state_read_byte((char *) b);
}

static bool state_read_int(int *i) {
    return state_read_bytes(i, sizeof(int));
}

static bool state_read_int4(int4 *i) {
    return state_read_bytes(i, 4);
}

static bool state_read_string(char *s, int4 maxlen) {
    s[0] = 0;
    int4 len;
    if (!state_read_int4(&len))
        return false;
    if (len >= maxlen)
        return false;
    s[len] = 0;
    return state_read_bytes(s, len);
}

bool read_shell_state() {
    int magic;
    int state_size;
    int state_version;
    
    if (!state_read_int4(&magic))
        return false;
    if (magic != FREE42_MAGIC)
        return false;
    int4 dummy;
    if (!state_read_int4(&dummy))
        return false;
    
    if (fread(&state_size, 1, sizeof(int), statefile) != sizeof(int))
        return false;
    if (fread(&state_version, 1, sizeof(int), statefile) != sizeof(int))
        return false;
    if (state_version < 0 || state_version > SHELL_VERSION)
        /* Unknown shell state version */
        return false;

    if (state_version >= 16) {
        if (!state_read_string(state.coreName, FILENAMELEN)) return false;
        if (!state_read_string(state.skinName, FILENAMELEN)) return false;
        if (!state_read_string(state.landscapeSkinName, FILENAMELEN)) return false;
        if (!state_read_string(state.printerTxtFileName, FILENAMELEN)) return false;
        if (!state_read_string(state.printerGifFileName, FILENAMELEN)) return false;
        if (!state_read_bool(&state.printerToTxtFile)) return false;
        if (!state_read_bool(&state.printerToGifFile)) return false;
        if (!state_read_int(&state.printerGifMaxLength)) return false;
        if (!state_read_bool(&state.alwaysOn)) return false;
        if (!state_read_byte(&state.keyClicks)) return false;
        if (!state_read_byte(&state.hapticFeedback)) return false;
        if (!state_read_byte(&state.orientationMode)) return false;
        if (!state_read_bool(&state.maintainSkinAspect[0])) return false;
        if (!state_read_bool(&state.maintainSkinAspect[1])) return false;
        if (!state_read_byte(&state.swipeDirectionMode)) return false;
        if (!state_read_byte(&state.popupAlphaKeyboard)) return false;
        if (!state_read_bool(&core_settings.matrix_singularmatrix)) return false;
        if (!state_read_bool(&core_settings.matrix_outofrange)) return false;
        if (!state_read_bool(&core_settings.auto_repeat)) return false;
        if (!state_read_bool(&core_settings.allow_big_stack)) return false;
        if (!state_read_bool(&core_settings.localized_copy_paste)) return false;
        if (!state_read_bool(&off_enable_flag)) return false;
        int4 shiftmapsize;
        if (!state_read_int4(&shiftmapsize)) return false;
        if (shiftmapsize > 0 && !shiftMap.read(statefile, (size_t) shiftmapsize)) return false;
    } else {
        struct old_state_type {
            int printerToTxtFile;
            int printerToGifFile;
            char printerTxtFileName[FILENAMELEN];
            char printerGifFileName[FILENAMELEN];
            int printerGifMaxLength;
            char skinName[FILENAMELEN];
            char landscapeSkinName[FILENAMELEN];
            int alwaysOn;
            int keyClicks;
            int hapticFeedback;
            int orientationMode;
            int maintainSkinAspect[2];
            bool offEnabled;
            char coreName[FILENAMELEN];
            bool matrix_singularmatrix;
            bool matrix_outofrange;
            bool auto_repeat;
            bool allow_big_stack;
            bool localized_copy_paste;
            int swipeDirectionMode;
            char popupAlphaKeyboard;
        };
        old_state_type old_state;
        memset(&old_state, 0, sizeof(old_state_type));
        if (!state_read_bytes(&old_state, state_size))
            return false;
        state.printerToTxtFile = old_state.printerToTxtFile;
        state.printerToGifFile = old_state.printerToGifFile;
        strcpy(state.printerTxtFileName, old_state.printerTxtFileName);
        strcpy(state.printerGifFileName, old_state.printerGifFileName);
        state.printerGifMaxLength = old_state.printerGifMaxLength;
        strcpy(state.skinName, old_state.skinName);
        strcpy(state.landscapeSkinName, old_state.landscapeSkinName);
        state.alwaysOn = old_state.alwaysOn;
        state.keyClicks = old_state.keyClicks;
        state.hapticFeedback = old_state.hapticFeedback;
        state.orientationMode = old_state.orientationMode;
        state.maintainSkinAspect[0] = old_state.maintainSkinAspect[0];
        state.maintainSkinAspect[1] = old_state.maintainSkinAspect[1];
        off_enable_flag = old_state.offEnabled;
        strcpy(state.coreName, old_state.coreName);
        core_settings.matrix_singularmatrix = old_state.matrix_singularmatrix;
        core_settings.matrix_outofrange = old_state.matrix_outofrange;
        core_settings.auto_repeat = old_state.auto_repeat;
        core_settings.allow_big_stack = old_state.allow_big_stack;
        core_settings.localized_copy_paste = old_state.localized_copy_paste;
        state.swipeDirectionMode = old_state.swipeDirectionMode;
        state.popupAlphaKeyboard = old_state.popupAlphaKeyboard;
    }
    
    init_shell_state(state_version);
    return true;
}

static bool state_write_byte(char c) {
    return fputc(c, statefile) != EOF;
}

static bool state_write_bytes(void *buf, int n) {
    return fwrite(buf, 1, n, statefile) == n;
}

static bool state_write_bool(bool b) {
    return state_write_byte(b);
}

static bool state_write_int(int i) {
    return state_write_bytes(&i, sizeof(int));
}

static bool state_write_int4(int4 i) {
    return state_write_bytes(&i, 4);
}

static bool state_write_string(char *s) {
    int4 len = (int4) strlen(s);
    if (!state_write_int4(len))
        return false;
    return state_write_bytes(s, len);
}

bool write_shell_state() {
    if (!state_write_int4(FREE42_MAGIC)) return false;
    if (!state_write_int4(0)) return false; // core version; obsolete
    if (!state_write_int4(0)) return false; // state size; obsolete
    if (!state_write_int4(SHELL_VERSION)) return false;

    if (!state_write_string(state.coreName)) return false;
    if (!state_write_string(state.skinName)) return false;
    if (!state_write_string(state.landscapeSkinName)) return false;
    if (!state_write_string(state.printerTxtFileName)) return false;
    if (!state_write_string(state.printerGifFileName)) return false;
    if (!state_write_bool(state.printerToTxtFile)) return false;
    if (!state_write_bool(state.printerToGifFile)) return false;
    if (!state_write_int(state.printerGifMaxLength)) return false;
    if (!state_write_bool(state.alwaysOn)) return false;
    if (!state_write_byte(state.keyClicks)) return false;
    if (!state_write_byte(state.hapticFeedback)) return false;
    if (!state_write_byte(state.orientationMode)) return false;
    if (!state_write_bool(state.maintainSkinAspect[0])) return false;
    if (!state_write_bool(state.maintainSkinAspect[1])) return false;
    if (!state_write_byte(state.swipeDirectionMode)) return false;
    if (!state_write_byte(state.popupAlphaKeyboard)) return false;
    if (!state_write_bool(core_settings.matrix_singularmatrix)) return false;
    if (!state_write_bool(core_settings.matrix_outofrange)) return false;
    if (!state_write_bool(core_settings.auto_repeat)) return false;
    if (!state_write_bool(core_settings.allow_big_stack)) return false;
    if (!state_write_bool(core_settings.localized_copy_paste)) return false;
    if (!state_write_bool(off_enable_flag)) return false;
    if (!state_write_int4((int4) shiftMap.nbytes())) return false;
    if (!shiftMap.write(statefile)) return false;

    return true;
}
