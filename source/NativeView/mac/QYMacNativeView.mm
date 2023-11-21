//
//  QYMacNativeView.m
//  QYView
//
//  Created by 全寅 on 2023/11/16.
//

#import "QYMacNativeView.h"

@implementation QYMacNativeView

- (void)mouseUp:(NSEvent *)event {
    if (observer) {
        observer->onMouseUp();
    } else {
        [super mouseUp:event];
    }
}

- (void)mouseDown:(NSEvent *)event {
    if (observer) {
        observer->onMouseDown();
    } else {
        [super mouseDown:event];
    }
}

- (void)mouseMoved:(NSEvent *)event {
    if (observer) {
        observer->onMouseMoved();
    } else {
        [super mouseMoved:event];
    }
}

@end
