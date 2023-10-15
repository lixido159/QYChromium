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
