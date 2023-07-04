#import "QYBaseWidget.h"
void QYBaseWidget::addChild(QYBaseWidget *child) {
    mChildWidgets.push_back(child);
    child->mParent = this;
}
