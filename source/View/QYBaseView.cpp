#include "QYBaseView.h"
#include "QYBaseCustomView.h"
QYBaseView::QYBaseView() {
    mCustomView = new QYBaseCustomView;
    mNodeLayout = std::make_shared<QYYogaLayout>(this);
}

IQYBaseView* QYBaseView::getParentView(){
    return mParentView;
}
void QYBaseView::setParentView(IQYBaseView *parentView){
    mParentView = parentView;
}

IQYBaseCustomBaseView* QYBaseView::getCustomView(){
    return mCustomView;
}

QYYogaLayout *QYBaseView::getNodeLayout() {
    return mNodeLayout.get();
}

void QYBaseView::addChildView(IQYBaseView *child) {
    YGNodeRef node = getNodeLayout()->getNode();
    YGNodeRef childNode = child->getNodeLayout()->getNode();
    YGNodeInsertChild(node, childNode, mChildViews.size());
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
void QYBaseView::setSize(QYSize size){
    mCustomView->setSize(size);
}
void QYBaseView::setRect(QYRect rect){
    mCustomView->setRect(rect);
}
void QYBaseView::setBackgroundColor(QY_Color color){
    mCustomView->setBackgroundColor(color);
}


float QYBaseView::getX(){
    return mCustomView->getX();
}
float QYBaseView::getY(){
    return mCustomView->getY();
}
float QYBaseView::getWidth(){
    return mCustomView->getWidth();
}
float QYBaseView::getHeight(){
    return mCustomView->getHeight();
}
QYSize QYBaseView::getSize(){
    return mCustomView->getSize();
}
QYRect QYBaseView::getRect(){
    return mCustomView->getRect();
}

void QYBaseView::requestLayout() {
    YGNodeRef node = getNodeLayout()->getNode();
    if (getParentView()) {
        QYSize size = getParentView()->getSize();
        YGNodeCalculateLayout(node, size.width, size.height, YGDirectionInherit);
        updateLayout();
    } else {
        //根节点的view，不改变尺寸
        YGNodeCalculateLayout(node, getSize().width, getSize().height, YGDirectionLTR);
        for (std::vector<IQYBaseView *>::iterator iter = mChildViews.begin(); iter != mChildViews.end(); iter++) {
            (*iter)->updateLayout();
        }

    }
}

void QYBaseView::updateLayout() {
    YGNodeRef node = getNodeLayout()->getNode();
    float top = YGNodeLayoutGetTop(node);
    float left = YGNodeLayoutGetLeft(node);
    float width = YGNodeLayoutGetWidth(node);
    float height = YGNodeLayoutGetHeight(node);
    setRect({left, top, width, height});
    for (std::vector<IQYBaseView *>::iterator iter = mChildViews.begin(); iter != mChildViews.end(); iter++) {
        (*iter)->updateLayout();
    }

}

