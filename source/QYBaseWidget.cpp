#import "QYBaseWidget.h"
void QYBaseWidget::addChild(QYBaseWidget *child) {
    mChildWidgets.push_back(child);
    child->mParent = this;
}


void QYBaseWidget::setProperty(std::string key, QYPropertyValue *value) {
    mPropertyValueMap.insert(std::pair(key, value));
}

QYPropertyValue* QYBaseWidget::getProperty(std::string key) {
    return mPropertyValueMap[key];
}
