//
//  QYMacNativeView.h
//  QYView
//
//  Created by 全寅 on 2023/11/16.
//

#import <Cocoa/Cocoa.h>
#import "IQYMouseEventObserver.h"
NS_ASSUME_NONNULL_BEGIN

@interface QYMacNativeView : NSView {
    IQYMouseEventObserver *observer;
}

@end

NS_ASSUME_NONNULL_END
