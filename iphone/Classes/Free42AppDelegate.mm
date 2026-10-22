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

#import "Free42AppDelegate.h"

static char version[32] = "";

@implementation Free42AppDelegate

- (void) applicationDidFinishLaunching:(UIApplication *)application {
    // Override point for customization after application launch
}

- (void) applicationWillTerminate:(UIApplication *)application {
    //
}

+ (const char *) getVersion {
    if (version[0] == 0) {
        NSString *appVersion = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
        strcpy(version, [appVersion UTF8String]);
        // Version string consists of up to three dot-separated numbers.
        // If there are three, change the last ".nn" to a letter.
        int pos, num;
        char c = 0;
        if (sscanf(version, "%*d.%*d.%n%d", &pos, &num) == 1) {
            c = 'a' + num - 1;
            version[pos - 1] = 0;
        }
        // If there are now two components, remove the second if it is ".0"
        size_t len = strlen(version);
        if (len > 2 && version[len - 2] == '.' && version[len - 1] == '0') {
            len -= 2;
            version[len] = 0;
        }
        // The first component consists of the major and minor version
        // components joined together. *sigh* Long story.
        memmove(version + 2, version + 1, len);
        version[1] = '.';
        len++;
        // Append that version letter we found in the first step
        if (c != 0) {
            version[len++] = c;
            version[len] = 0;
        }
    }   
    return version;
}

@end
