#include "QYBaseView.h"

void QYBaseView::addChild(QYBaseView *child) {
    mChildViews.push_back(child);
    child->mParent = this;
    mView->addChildView(child->mView);
}
