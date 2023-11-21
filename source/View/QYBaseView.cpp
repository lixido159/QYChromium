#include "QYBaseView.h"

IQYBaseView* QYBaseView::getParentView(){
    return mParentView;
}
void QYBaseView::setParentView(IQYBaseView *parentView){
    mParentView = parentView;
}

IQYBaseCustomBaseView* QYBaseView::getCustomView(){
    return mCustomView;
}
void QYBaseView::setCustomView(IQYBaseCustomBaseView *customView){
    mCustomView = customView;
}

void QYBaseView::addChildView(IQYBaseView *child) {
    mChildViews.push_back(child);
    child->setParentView(this);
    mCustomView->addChildView(child->getCustomView());
}


void QYBaseView::setX(float x){
    mCustomView->setX(x);
}
void QYBaseView::setY(float y){
    mCustomView->setY(y);
}
void QYBaseView::setWidth(float width){
    mCustomView->setWidth(width);
}
void QYBaseView::setHeight(float height){
    mCustomView->setHeight(height);
}
void QYBaseView::setSize(float width, float height){
    mCustomView->setSize(width, height);
}
void QYBaseView::setRect(float x, float y, float width, float height){
    mCustomView->setRect(x, y, width, height);
}
void QYBaseView::setBackgroundColor(QY_Color color){
    mCustomView->setBackgroundColor(color);
}
void QYBaseView::addChildView(IQYBaseCustomBaseView *view){
    mCustomView->addChildView(view);
}

void *QYBaseView::getNativeView(){
    return mCustomView->getNativeView();
}

