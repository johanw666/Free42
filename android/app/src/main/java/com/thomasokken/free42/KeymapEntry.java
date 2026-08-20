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

package com.thomasokken.free42;

import java.io.ByteArrayOutputStream;
import java.util.StringTokenizer;

import android.view.KeyEvent;

/** @noinspection ALL */
public class KeymapEntry {
    private static final int KEYMAP_MAX_MACRO_LENGTH = 31;
    public boolean ctrl;
    public boolean alt;
    public boolean shift;
    public boolean numpad;
    public boolean numlock;
    public boolean cshift;
    public String keychar;
    public byte[] macro;

    public static KeymapEntry parse(String line, int lineno) {
        int p = line.indexOf('#');
        if (p != -1)
            line = line.substring(0, p);
        p = line.indexOf('\n');
        if (p != -1)
            line = line.substring(0, p);
        p = line.indexOf('\r');
        if (p != -1)
            line = line.substring(0, p);

        p = line.indexOf(':');
        if (p != -1) {
            StringTokenizer t = new StringTokenizer(line.substring(0, p), " \t", false);
            String val = line.substring(p + 1);
            String tok;
            boolean ctrl = false;
            boolean alt = false;
            boolean numpad = false;
            boolean numlock = false;
            boolean shift = false;
            boolean cshift = false;
            String keychar = null;
            boolean done = false;
            ByteArrayOutputStream macro = new ByteArrayOutputStream();
            int macrolen = 0;
            
            /* Parse keycode */
            while (t.hasMoreTokens()) {
                tok = t.nextToken();
                if (done) {
                    System.err.println("Keymap, line " + lineno + ": Excess tokens in key spec.");
                    return null;
                }
                if (tok.equalsIgnoreCase("ctrl"))
                    ctrl = true;
                else if (tok.equalsIgnoreCase("alt"))
                    alt = true;
                else if (tok.equalsIgnoreCase("numpad"))
                    numpad = true;
                else if (tok.equalsIgnoreCase("numlock"))
                    numlock = true;
                else if (tok.equalsIgnoreCase("shift"))
                    shift = true;
                else if (tok.equalsIgnoreCase("cshift"))
                    cshift = true;
                else {
                    boolean success = false;
                    try {
                        if (tok.length() > 2 && tok.substring(0, 2).equalsIgnoreCase("0x")) {
                            keychar = "" + (char) Integer.parseInt(tok.substring(2), 16);
                            success = true;
                        }
                    } catch (NumberFormatException e) {}
                    if (!success) {
                        keychar = tok;
                        int keycode = KeyEvent.keyCodeFromString(keychar);
                        if (keycode != KeyEvent.KEYCODE_UNKNOWN) {
                            int kc = numpad_normalize(keycode);
                            if (kc != 0) {
                                keychar = "" + (char) kc;
                                numpad = true;
                            }
                        }
                    }
                    done = true;
                }
            }
            if (!done) {
                System.err.println("Keymap, line " + lineno + ": Unrecognized keycode.");
                return null;
            }
            
            /* Parse macro */
            t = new StringTokenizer(val, " \t");
            while (t.hasMoreTokens()) {
                tok = t.nextToken();
                short k;
                try {
                    k = Short.parseShort(tok);
                } catch (NumberFormatException e) {
                    System.err.println("Keymap, line " + lineno + ": Bad value (" + tok + ") in macro.");
                    return null;
                }
                if (k < 1 || k > 255) {
                    System.err.println("Keymap, line " + lineno + ": Bad value (" + tok + ") in macro.");
                    return null;
                } else if (macrolen == KEYMAP_MAX_MACRO_LENGTH) {
                    System.err.println("Keymap, line " + lineno + ": Macro too long (max=" + KEYMAP_MAX_MACRO_LENGTH + ").");
                    return null;
                } else
                    macro.write(k);
            }

            KeymapEntry entry = new KeymapEntry();
            entry.ctrl = ctrl;
            entry.alt = alt;
            entry.numpad = numpad;
            entry.numlock = numlock;
            entry.shift = shift;
            entry.cshift = cshift;
            entry.keychar = keychar;
            entry.macro = macro.toByteArray();
            return entry;
        } else
            return null;
    }

    public int match(String keychar, boolean ctrl, boolean alt, boolean shift, boolean shift_mismatch_allowed,
                     boolean numpad, boolean numlock, boolean cshift) {
        if (!keychar.equals(this.keychar)
                || ctrl != this.ctrl
                || alt != this.alt
                || !shift_mismatch_allowed && shift != this.shift
                || !numpad && this.numpad
                || !numlock && this.numlock
                || !cshift && this.cshift)
            return 0;
        return (numpad == this.numpad ? 18 : 9)
                + (numlock == this.numlock ? 6 : 3)
                + (cshift == this.cshift ? 2 : 1);
    }

    public static final int MAX_MATCH_QUALITY = 26;

    public static int numpad_normalize(int keycode) {
        switch (keycode) {
            case KeyEvent.KEYCODE_NUMPAD_0: return '0';
            case KeyEvent.KEYCODE_NUMPAD_1: return '1';
            case KeyEvent.KEYCODE_NUMPAD_2: return '2';
            case KeyEvent.KEYCODE_NUMPAD_3: return '3';
            case KeyEvent.KEYCODE_NUMPAD_4: return '4';
            case KeyEvent.KEYCODE_NUMPAD_5: return '5';
            case KeyEvent.KEYCODE_NUMPAD_6: return '6';
            case KeyEvent.KEYCODE_NUMPAD_7: return '7';
            case KeyEvent.KEYCODE_NUMPAD_8: return '8';
            case KeyEvent.KEYCODE_NUMPAD_9: return '9';
            case KeyEvent.KEYCODE_NUMPAD_ADD: return '+';
            case KeyEvent.KEYCODE_NUMPAD_SUBTRACT: return '-';
            case KeyEvent.KEYCODE_NUMPAD_MULTIPLY: return '*';
            case KeyEvent.KEYCODE_NUMPAD_DIVIDE: return '/';
            case KeyEvent.KEYCODE_NUMPAD_COMMA: return ',';
            case KeyEvent.KEYCODE_NUMPAD_DOT: return '.';
            case KeyEvent.KEYCODE_NUMPAD_ENTER: return 10;
            case KeyEvent.KEYCODE_NUMPAD_EQUALS: return '=';
            case KeyEvent.KEYCODE_NUMPAD_LEFT_PAREN: return '(';
            case KeyEvent.KEYCODE_NUMPAD_RIGHT_PAREN: return ')';
            default: return 0;
        }
    }
}
