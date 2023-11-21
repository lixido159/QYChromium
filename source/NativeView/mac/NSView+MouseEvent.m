//
//  NSView+MouseEvent.m
//  QYView
//
//  Created by 全寅 on 2023/11/16.
//

#import "NSView+MouseEvent.h"
#import "QYRuntime.h"
#import <objc/runtime.h>

@interface NSView()
@property (readwrite, nonatomic, strong) NSTrackingArea *trackingArea;
@end

@implementation NSView (MouseEvent)

+ (void)load {
    instanceMethodSwizzling([NSView class], @selector(updateTrackingAreas), @selector(qy_updateTrackingAreas));
}



- (void)qy_updateTrackingAreas {
    [self qy_updateTrackingAreas];
    if (self.trackingArea != nil) {
        [self removeTrackingArea:self.trackingArea];
        self.trackingArea = nil;
    }
    NSTrackingAreaOptions options = NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInActiveApp | NSTrackingInVisibleRect;
    self.trackingArea = [[NSTrackingArea alloc] initWithRect:self.bounds
                                                            options:options
                                                              owner:self
                                                           userInfo:nil];
    [self addTrackingArea:self.trackingArea];
}

- (void)mouseUp:(NSEvent *)event {
    
}


- (void)mouseDown:(NSEvent *)event {

}

- (void)mouseMoved:(NSEvent *)event {

}

- (void)mouseEntered:(NSEvent *)event {
    
}

- (void)mouseExited:(NSEvent *)event {
    
}

- (void)setTrackingArea:(NSTrackingArea *)trackingArea {
    objc_setAssociatedObject(self, @selector(trackingArea), trackingArea, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}


- (NSTrackingArea *)trackingArea {
    return objc_getAssociatedObject(self, @selector(trackingArea));
}

@end
