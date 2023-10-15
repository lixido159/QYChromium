#include "QYBaseWidget.h"
#include "QYPropertySetter.h"
void QYBaseWidget::addChildWidget(QYBaseWidget *child) {
    mChildWidgets.push_back(child);
    child->setParentWidget(this);
}

void QYBaseWidget::setProperty(std::string key, QYPropertyValue *value) {
    static QYPropertySetter *setter = new QYPropertySetter;
    mProptyValueMap.insert(std::pair(key, value));
    setter->setProperty(mView, value);
}

QYPropertyValue* QYBaseWidget::getProperty(std::string key) {
    return mProptyValueMap[key];
}

std::map<std::string, QYPropertyValue *> QYBaseWidget::getProptyValueMap() {
    return mProptyValueMap;
}

QYBaseWidget * QYBaseWidget::getParentWidget() {
    return mParentWidget;
}
void QYBaseWidget::setParentWidget(QYBaseWidget *parentWidget) {
    mParentWidget = parentWidget;
}

void QYBaseWidget::setView(IQYBaseView *view) {
    mView = view;
}

IQYBaseView* QYBaseWidget::getView() {
    return mView;
}
