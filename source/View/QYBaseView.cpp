#include "QYBaseView.h"
#include "QYBaseCustomView.h"
QYBaseView::QYBaseView() {
    mCustomView = std::make_shared<QYBaseCustomView>();
    mNodeLayout = std::make_shared<QYYogaLayout>(this);
}

std::shared_ptr<IQYBaseView> QYBaseView::getParentView(){
    auto parent = mParentView.lock();
    if (parent) {
        return parent;
    }
    return nullptr;
}
void QYBaseView::setParentView(std::shared_ptr<IQYBaseView> parentView){
    mParentView = parentView;
}

std::shared_ptr<IQYBaseCustomBaseView> QYBaseView::getCustomView(){
    return mCustomView;
}

std::vector<std::shared_ptr<IQYBaseView>> QYBaseView::getChildViews() {
    return mChildViews;
}

QYYogaLayout *QYBaseView::getNodeLayout() {
    return mNodeLayout.get();
}

void QYBaseView::addChildView(std::shared_ptr<IQYBaseView> child) {
    YGNodeRef node = getNodeLayout()->getNode();
    YGNodeRef childNode = child->getNodeLayout()->getNode();
    YGNodeInsertChild(node, childNode, mChildViews.size());
    mChildViews.push_back(child);
    child->setParentView(shared_from_this());
    mCustomView->addChildView(child->getCustomView());
 
}

void QYBaseView::removeChildView(std::shared_ptr<IQYBaseView> child) {
    mCustomView->removeChildView(child->getCustomView());
    YGNodeRef node = getNodeLayout()->getNode();
    YGNodeRef childNode = child->getNodeLayout()->getNode();
    YGNodeRemoveChild(node, childNode);
    mChildViews.erase(std::remove(mChildViews.begin(), mChildViews.end(), child), mChildViews.end());
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
    std::shared_ptr<IQYBaseView>  parentView = getParentView();
    if (parentView) {
        QYSize size = parentView->getSize();
        YGNodeCalculateLayout(YGNodeGetParent(node), size.width, size.height, YGDirectionInherit);
        parentView->updateLayout();
    } else {
        //根节点的view，不改变尺寸
        YGNodeCalculateLayout(node, getSize().width, getSize().height, YGDirectionLTR);
        for (std::vector<std::shared_ptr<IQYBaseView>>::iterator iter = mChildViews.begin(); iter != mChildViews.end(); iter++) {
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
    for (std::vector<std::shared_ptr<IQYBaseView>>::iterator iter = mChildViews.begin(); iter != mChildViews.end(); iter++) {
        (*iter)->updateLayout();
    }

}

