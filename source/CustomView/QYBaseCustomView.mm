//
//  QYBaseCustomView.cpp
//  libEVO
//
//  Created by yinquan on 2023/7/5.
//

#include "QYBaseCustomView.h"
#include "AppKit/AppKit.h"
#include "QYMacNativeView.h"

#define toNativeView(view) ((__bridge QYMacNativeView *)view)
#define nativeView toNativeView(mNativeView)



QYBaseCustomView::QYBaseCustomView() {
    QYMacNativeView *view = [[QYMacNativeView alloc] init];
    mNativeView = (__bridge_retained void *)view;
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
void QYBaseCustomView::setSize(QYSize size){
    [nativeView setFrameSize:CGSizeMake(size.width, size.height)];
}
void QYBaseCustomView::setRect(QYRect rect){
    [nativeView setFrame:CGRectMake(rect.x, rect.y, rect.width, rect.height)];
}
void QYBaseCustomView::setBackgroundColor(QY_Color color){
    nativeView.wantsLayer = YES;
    nativeView.layer.backgroundColor = [NSColor colorWithRed:color.r/255.0 green:color.g/255.0 blue:color.b/255.0 alpha:color.a/255.0].CGColor;
}

float QYBaseCustomView::getX(){
    return NSMinX(nativeView.frame);
}
float QYBaseCustomView::getY(){
    return NSMinY(nativeView.frame);
}
float QYBaseCustomView::getWidth(){
    return NSWidth(nativeView.frame);
}
float QYBaseCustomView::getHeight(){
    return NSHeight(nativeView.frame);
}
QYSize QYBaseCustomView::getSize(){
    return {getWidth(), getHeight()};
}
QYRect QYBaseCustomView::getRect(){
    return {getX(), getY(), getWidth(), getHeight()};
}


void QYBaseCustomView::addChildView(std::shared_ptr<IQYBaseCustomBaseView> view){
    [nativeView addSubview:toNativeView(view->getNativeView())];
}

void QYBaseCustomView::removeFromParentView() {
    [toNativeView(getNativeView()) removeFromSuperview];
}

void *QYBaseCustomView::getNativeView(){
    return mNativeView;
}

void QYBaseCustomView::setMouseEventObserver(IQYMouseEventObserver *observer) {
    nativeView->observer = observer;
}
