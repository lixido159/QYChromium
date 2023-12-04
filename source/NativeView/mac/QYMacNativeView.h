//
//  QYMacNativeView.h
//  QYView
//
//  Created by yinquan on 2023/11/16.
//

#import <Cocoa/Cocoa.h>
#import "IQYMouseEventObserver.h"
NS_ASSUME_NONNULL_BEGIN

@interface QYMacNativeView : NSView {
@public
    IQYMouseEventObserver *observer;
}

@end

NS_ASSUME_NONNULL_END
