#include "QYBaseWidget.h"
#include "QYPropertySetter.h"
#include "QYFactory.h"
#include "QYJSContext.h"

QYBaseWidget::QYBaseWidget(std::shared_ptr<QYPageCompContext> context, std::string type):mPageCompContext(context), mType(type) {

}

void QYBaseWidget::addChildWidget(QYBaseWidget *child) {
    mChildWidgets.push_back(child);
    child->setParentWidget(this);
}

void QYBaseWidget::setProperty(std::shared_ptr<QYPropertyValue> value, bool noLayout) {
    static QYPropertySetter *setter = new QYPropertySetter;
    mProptyValueMap.insert(std::pair(value->getKey(), value));
    setter->setProperty(mView, value.get(), noLayout);
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




QYBaseWidget *QYBaseWidget::getChildWidgetById(std::string childId) {
    for (std::vector<QYBaseWidget *>::iterator iter = mChildWidgets.begin(); iter !=mChildWidgets.end(); iter++) {
        QYBaseWidget *childWidget = *iter;
        QYPropertyValue *propty = childWidget->getProperty("id");
        if (propty &&  childId.compare(propty->getStringValue()) == 0) {
            return childWidget;
        }
        QYBaseWidget *result = childWidget->getChildWidgetById(childId);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

std::shared_ptr<QYPageCompContext> QYBaseWidget::getPageCompContext() {
    return mPageCompContext;
}

QYJSValue *QYBaseWidget::getElementValue() {
    if (mElementValue == nullptr) {
        mElementValue.reset(mPageCompContext->getJSContext()->newObject());
        registerElementInterface();
    }
    return mElementValue.get();
}

void QYBaseWidget::performExpandViewTree() {
    IQYBaseView *view = createViewWithType(mType);
    setView(view);
    if (getParentWidget()) {
        getParentWidget()->getView()->addChildView(view);
    }
    for(QYBaseWidget *widget : mChildWidgets) {
        widget->performExpandViewTree();
    }

}

void QYBaseWidget::registerElementInterface() {
    mElementValue->setFunction("getComponent", [this](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue * {
        return mPageCompContext->getPageCompValue();
    });
}

void QYBaseWidget::requestLayout() {
    mView->requestLayout();
}

void QYBaseWidget::onSizeChange() {
    requestLayout();
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

