#include "QYBaseWidget.h"
#include "QYPropertySetter.h"


QYBaseWidget::QYBaseWidget(std::shared_ptr<QYPageCompContext> context):mPageCompContext(context) {
    
}

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
    if (mProptyValueMap.find(key) == mProptyValueMap.end()) {
        return nullptr;
    }
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

QYJSValue * mouseEventToJSValue(std::shared_ptr<QYJSContext> jsContext, const QYMouseEvent& mouseEvent) {
    QYJSValue *obj = new QYJSValue(jsContext);
    obj->setValue("x", new QYJSValue(jsContext, mouseEvent.x));
    obj->setValue("y", new QYJSValue(jsContext, mouseEvent.y));
    obj->setValue("type", new QYJSValue(jsContext, static_cast<double>(mouseEvent.type)));
    return obj;
}

void QYBaseWidget::callMouseEvent(std::string event, const QYMouseEvent& mouseEvent) {
    QYPropertyValue *value = getProperty(event);
    if (!value) {
        return;
    }
    std::string funcName = value->getStringValue();
    QYJSValue *pageCompValue = mPageCompContext->getPageCompValue();
    std::shared_ptr<QYJSContext> jsContext = mPageCompContext->getJSContext();
    pageCompValue->call("call", {new QYJSValue(jsContext, funcName), mouseEventToJSValue(jsContext, mouseEvent)});
}

void QYBaseWidget::onMouseUp(const QYMouseEvent& mouseEvent) {
    callMouseEvent("bindmouseup", mouseEvent);
}
void QYBaseWidget::onMouseDown(const QYMouseEvent& mouseEvent) {
    callMouseEvent("bindmousedown", mouseEvent);
}
void QYBaseWidget::onMouseMoved(const QYMouseEvent& mouseEvent) {
    callMouseEvent("bindmousemove", mouseEvent);
}

