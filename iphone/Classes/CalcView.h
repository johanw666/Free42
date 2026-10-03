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

#import <UIKit/UIKit.h>
#import "shell_skin.h"

#define FILENAMELEN 1024

void get_keymap(keymap_entry **map, int *length);


@interface CalcView : UIView {
    UIButton *keyboardShortcutsButton;
    bool keyboardShortcutsShowing;
}

@property (nonatomic, retain) IBOutlet UIButton *keyboardShortcutsButton;

- (void) awakeFromNib;
- (void) layoutSubviews;
+ (BOOL) isPortrait;
+ (CGFloat) width;
+ (CGFloat) height;
- (void) touchesBegan: (NSSet *) touches withEvent: (UIEvent *) event;
+ (void) repaint;
+ (void) quit;
+ (void) loadState:(const char *)name;
+ (void) enterBackground;
+ (void) leaveBackground;
- (void) doCopy;
- (void) doPaste;
- (void) setTimeout:(int) which;
- (void) cancelTimeout3;
- (void) setRepeater:(int) delay;
- (void) cancelRepeater;
+ (void) alphaKeyboardAlpha:(unsigned short) code;
+ (void) alphaKeyboardDown:(int) key;
+ (void) alphaKeyboardUp;
+ (void) keyFeedback;
+ (void) stopTextPrinting;
+ (void) stopGifPrinting;
- (void) setActive:(bool) active;
- (IBAction) toggleKeyboardShortcuts:(id)sender;

@end
