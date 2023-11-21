#include "QYBaseWidget.h"
#include "QYPropertySetter.h"
void QYBaseWidget::addChildWidget(QYBaseWidget *child) {
    mChildWidgets.push_back(child);
    child->setParentWidget(this);
}

void QYBaseWidget::setProperty(std::shared_ptr<QYPropertyValue> value) {
    static QYPropertySetter *setter = new QYPropertySetter;
    mProptyValueMap.insert(std::pair(value->getKey(), value));
    setter->setProperty(mView, value.get());
}

QYPropertyValue* QYBaseWidget::getProperty(std::string key) {
    return mProptyValueMap[key].get();
}

std::map<std::string, std::shared_ptr<QYPropertyValue>> QYBaseWidget::getProptyValueMap() {
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
    mView->getCustomView()->setMouseEventObserver(this);
}

IQYBaseView* QYBaseWidget::getView() {
    return mView;
}

void QYBaseWidget::onMouseUp() {
    
}
void QYBaseWidget::onMouseDown() {
    
}
void QYBaseWidget::onMouseMoved() {
    
}

