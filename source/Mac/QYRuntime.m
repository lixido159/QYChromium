//
//  QYRuntime.m
//  QYView
//
//  Created by yinquan on 2023/11/16.
//

#import "QYRuntime.h"
#import <objc/runtime.h>

void instanceMethodSwizzling(Class cls, SEL originalSelector, SEL swizzledSelector) {
    Method originalMethod = class_getInstanceMethod(cls, originalSelector);
    Method swizzledMethod = class_getInstanceMethod(cls, swizzledSelector);
    
    BOOL didAddMethod = class_addMethod(cls, originalSelector, method_getImplementation(swizzledMethod), method_getTypeEncoding(swizzledMethod));
    
    if (didAddMethod) {
        class_replaceMethod(cls, swizzledSelector, method_getImplementation(originalMethod), method_getTypeEncoding(originalMethod));
    } else {
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}

void classMethodSwizzling(Class cls, SEL originalSelector, SEL swizzledSelector) {
    Class metaClass = objc_getMetaClass(object_getClassName(cls));
    
    Method originalMethod = class_getClassMethod(metaClass, originalSelector);
    Method swizzledMethod = class_getClassMethod(metaClass, swizzledSelector);
    
    BOOL didAddMethod = class_addMethod(metaClass, originalSelector, method_getImplementation(swizzledMethod), method_getTypeEncoding(swizzledMethod));
    
    if (didAddMethod) {
        class_replaceMethod(metaClass, swizzledSelector, method_getImplementation(originalMethod), method_getTypeEncoding(originalMethod));
    } else {
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}

BOOL is_subclass_of(Class cls1, Class cls2) {
    if (cls1 == Nil || cls2 == Nil)
        return NO ;
    
    if (class_getSuperclass(cls1) == cls2)
        return YES ;
    else
        return is_subclass_of(class_getSuperclass(cls1), cls2) ;
}

