#include "QYBaseView.h"
#include "ui/views/background.h"
using namespace views;

void QYBaseView::addChild(QYBaseView *child) {
    mChildViews.push_back(child);
    child->mParent = this;
    mView->AddChildView(std::unique_ptr<View>(child->mView));
}
