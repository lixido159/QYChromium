//
//  QYRuntime.h
//  QYView
//
//  Created by yinquan on 2023/11/16.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
void instanceMethodSwizzling(Class cls, SEL originalSelector, SEL swizzledSelector);
void classMethodSwizzling(Class cls, SEL originalSelector, SEL swizzledSelector);
BOOL is_subclass_of(Class cls1, Class cls2);


NS_ASSUME_NONNULL_END
