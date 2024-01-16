//
//  QYDom.cpp
//  QYView
//
//  Created by yinquan on 2023/12/7.
//

#include "QYDom.h"
#include "QYJSContext.h"
#include "QYBaseWidget.h"
#include "QYJSValue.h"

QYDom::QYDom(std::shared_ptr<QYBaseWidget> widget):mWidget(widget) {
    
}

QYJSValue *QYDom::getValue() {
    if (mJSValue == nullptr) {
        QYJSValue *dom = mWidget->getPageCompContext()->getJSContext()->newObject();
        mJSValue.reset(dom);
        registerDomValueInterface();
    }
    return mJSValue.get();
}

void QYDom::registerDomValueInterface() {
    mJSValue->setFunction("getElementById", [this](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue *{
        std::shared_ptr<QYBaseWidget> widget = mWidget->getChildWidgetById(paramsValue->getValue(0)->toString());
        if (!widget) {
            return nullptr;
        }
        return widget->getElementValue();
    });
}



