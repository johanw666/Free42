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

#import "CalcView.h"
#import "Free42AppDelegate.h"
#import "shell_skin.h"

@implementation CalcView

@synthesize keyboardShortcutsMenuItem;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
        self.postsFrameChangedNotifications = YES;
        [[NSNotificationCenter defaultCenter]
             addObserver:self
             selector:@selector(frameDidChange:)
             name:NSViewFrameDidChangeNotification
             object:self];
        keyboardShortcutsShowing = false;
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
    skin_repaint(&rect, keyboardShortcutsShowing);
}

- (BOOL) acceptsFirstResponder {
    return YES;
}

- (void) viewDidMoveToWindow {
    [[self.window standardWindowButton:NSWindowZoomButton] setEnabled:NO];
    [super viewDidMoveToWindow];
}

- (void)frameDidChange:(NSNotification*)notification {
    int sw, sh;
    skin_get_size(&sw, &sh);
    state.mainWindowWidth = self.frame.size.width;
    state.mainWindowHeight = self.frame.size.height;
    [self scaleUnitSquareToSize:NSMakeSize(self.bounds.size.width / sw, self.bounds.size.height / sh)];
    [self setNeedsDisplay:YES];
}

- (void)mouseDown:(NSEvent *)theEvent {
    NSPoint loc = [theEvent locationInWindow];
    loc = [self convertPoint:loc fromView:nil];
    calc_mousedown((int) loc.x, (int) loc.y);
}

- (void)mouseUp:(NSEvent *)theEvent {
    calc_mouseup();
}

// Handle Shift-Tab and NumPad-Enter
static unsigned short keychar_normalize(unsigned char c) {
    if (c == 25)
        return 9;
    else if (c == 3)
        return 13;
    else
        return c;
}

- (void)keyDown:(NSEvent *)theEvent {
    if ([theEvent isARepeat])
        return;

    NSUInteger flags = [theEvent modifierFlags];
    NSUInteger flags2 = flags
                & NSEventModifierFlagDeviceIndependentFlagsMask
                & ~(NSEventModifierFlagControl | NSEventModifierFlagOption);
    NSString *c = [theEvent characters];
    NSString *s = [theEvent charactersByApplyingModifiers:flags2];
    NSString *ss = [theEvent charactersByApplyingModifiers:flags2 ^ NSEventModifierFlagShift];
    if ([c length] == 0 && [s length] == 0 && [ss length] == 0)
        return;

    unichar ch = [c length] == 0 ? 0 : [c characterAtIndex:0];
    unsigned short keyCode = [theEvent keyCode];

    if (ch == 127 || ch >= 0xf700 && ch <= 0xf8ff) {
        if (ch == NSHelpFunctionKey)
            ch = NSInsertFunctionKey;
        else if (ch == NSUpArrowFunctionKey || ch == NSDownArrowFunctionKey
                || ch == NSLeftArrowFunctionKey || ch == NSRightArrowFunctionKey)
            flags &= ~NSEventModifierFlagNumericPad;
        calc_keydown(ch, ch, ch, flags, keyCode);
    } else {
        unichar cs = [s length] == 0 ? 0 : keychar_normalize([s characterAtIndex:0]);
        unichar css = [ss length] == 0 ? 0 : keychar_normalize([ss characterAtIndex:0]);
        calc_keydown(cs, css, ch, flags, keyCode);
    }
}

- (void)keyUp:(NSEvent *)theEvent {
    if ([theEvent isARepeat])
        return;
    calc_keyup([theEvent keyCode]);
}

- (void)flagsChanged:(NSEvent *)theEvent {
    calc_keymodifierschanged([theEvent modifierFlags]);
}

- (IBAction) toggleKeyboardShortcuts:(id)sender {
    keyboardShortcutsShowing = !keyboardShortcutsShowing;
    [keyboardShortcutsMenuItem setState:keyboardShortcutsShowing ? NSControlStateValueOn : NSControlStateValueOff];
    [self setNeedsDisplay:YES];
}

- (void) viewDidChangeEffectiveAppearance {
    [super viewDidChangeEffectiveAppearance];
    self.needsDisplay = YES;
}

@end
