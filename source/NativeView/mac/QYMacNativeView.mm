//
//  QYMacNativeView.m
//  QYView
//
//  Created by yinquan on 2023/11/16.
//

#import "QYMacNativeView.h"
#import "QYMouseEvent.h"

@interface QYMacNativeView()
@property (readwrite, nonatomic, strong) NSTrackingArea *trackingArea ;
@end

@implementation QYMacNativeView


- (void)updateTrackingAreas
{
    if (self.trackingArea != nil) {
        [self removeTrackingArea:self.trackingArea] ;
    }

    self.trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                                     options:NSTrackingMouseMoved | NSTrackingActiveInActiveApp
                                                       owner:self
                                                    userInfo:nil] ;
    [self addTrackingArea:self.trackingArea] ;
}

- (void)mouseUp:(NSEvent *)event {
    if (observer) {
        QYMouseEvent mouseEvent(static_cast<QYMouseEventType>(event.type), (int)event.locationInWindow.x, (int)event.locationInWindow.y);
        observer->onMouseUp(mouseEvent);
    } else {
        [super mouseUp:event];
    }
}

- (void)mouseDown:(NSEvent *)event {
    if (observer) {
        QYMouseEvent mouseEvent(static_cast<QYMouseEventType>(event.type), (int)event.locationInWindow.x, (int)event.locationInWindow.y);
        observer->onMouseDown(mouseEvent);
    } else {
        [super mouseDown:event];
    }
}

- (void)mouseMoved:(NSEvent *)event {
    if (observer) {
        QYMouseEvent mouseEvent(static_cast<QYMouseEventType>(event.type), (int)event.locationInWindow.x, (int)event.locationInWindow.y);
        observer->onMouseMoved(mouseEvent);
    } else {
        [super mouseMoved:event];
    }
}

@end
