//
//  QYBaseCustomView.cpp
//  libEVO
//
//  Created by yinquan on 2023/7/5.
//

#include "QYBaseCustomView.h"
#include "AppKit/AppKit.h"


#define toNativeView(view) ((__bridge NSView *)view)
#define nativeView toNativeView(mNativeView)


QYBaseCustomView::QYBaseCustomView() {
    mNativeView = (__bridge_retained void *)[[NSView alloc] init];
}

void QYBaseCustomView::setX(float x){
    [nativeView setFrameOrigin:CGPointMake(x, nativeView.frame.origin.y)];
}
void QYBaseCustomView::setY(float y){
    [nativeView setFrameOrigin:CGPointMake(nativeView.frame.origin.x, y)];
}
void QYBaseCustomView::setWidth(float width){
    [nativeView setFrameSize:CGSizeMake(width, nativeView.frame.size.height)];
}
void QYBaseCustomView::setHeight(float height){
    [nativeView setFrameSize:CGSizeMake(nativeView.frame.size.width, height)];
}
void QYBaseCustomView::setSize(float width, float height){
    [nativeView setFrameSize:CGSizeMake(width, height)];
}
void QYBaseCustomView::setRect(float x, float y, float width, float height){
    [nativeView setFrame:CGRectMake(x, y, width, height)];
}
void QYBaseCustomView::setBackgroundColor(int r, int g, int b, int a){
    nativeView.wantsLayer = YES;
    nativeView.layer.backgroundColor = [NSColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a/255.0].CGColor;
}
void QYBaseCustomView::addChildView(IQYBaseCustomBaseView *view){
    [nativeView addSubview:toNativeView(view->getNativeView())];
}

void *QYBaseCustomView::getNativeView(){
    return mNativeView;
}