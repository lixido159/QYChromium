//
//  QYContextJSValue.cpp
//  QYView
//
//  Created by yinquan on 2023/12/4.
//

#include "QYContextJSValue.h"
#include "QYPageCompContext.h"
#include "QYJSContext.h"
QYContextJSValue::QYContextJSValue(std::weak_ptr<QYPageCompContext> pageCompContext):mPageCompContext(pageCompContext) {
    auto compContext = pageCompContext.lock();
    QYJSValue *contextObjectValue = compContext->getJSContext()->newObject();
    QYJSValue *dataValue = compContext->getJSContext()->newObject();
    contextObjectValue->setValue("data", dataValue);
    mContextObjectValue.reset(contextObjectValue);
    registerDataInterface();
}

std::map<std::string, QYJSValue *> QYContextJSValue::getDataMap() {
    return mDataMap;
}

QYJSValue* QYContextJSValue::getValue() {
    return mContextObjectValue.get();
}
QYJSValue* QYContextJSValue::getDataValue() {
    return mContextObjectValue->getValue("data");
}


std::shared_ptr<QYExpResult> QYContextJSValue::getResultForKey(std::string key) {
    if (mDataMap.find(key) != mDataMap.end()) {
        QYJSValue *value = mDataMap[key];
        if (value->isNumber()) {
            return std::make_shared<QYExpResult>(QYExpResultType::Number, value->toNumber());
        } else if (value->isString()) {
            return std::make_shared<QYExpResult>(QYExpResultType::String, value->toString());
        } else if (value->isBoolean()) {
            return std::make_shared<QYExpResult>(QYExpResultType::Boolean, value->toBoolean());
        }
    }
    return std::make_shared<QYExpResult>();
}

QYExpResultType QYContextJSValue::getTypeForKey(std::string key) {
    if (mDataMap.find(key) != mDataMap.end()) {
        QYJSValue *value = mDataMap[key];
        if (value->isNumber()) {
            return QYExpResultType::Number;
        } else if (value->isString()) {
            return QYExpResultType::String;
        } else if (value->isBoolean()) {
            return QYExpResultType::Boolean;
        } else if (value->isObject()) {
            return QYExpResultType::Object;
        }
    }
    return QYExpResultType::None;
}

bool QYContextJSValue::hasValueForKey(std::string key) {
    return mDataMap.find(key) != mDataMap.end();
}

void QYContextJSValue::registerDataInterface() {
    getDataValue()->setFunction("update", [this](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue * {
        std::string key = paramsValue->getValue(0)->toString();
        auto iter = mDataMap.find(key);
        if (iter != mDataMap.end()) {
            mDataMap.erase(iter);
        }
        mDataMap.insert(std::pair(key, paramsValue->getValue(1)));
        auto pageContext = mPageCompContext.lock();
        if (pageContext) {
            pageContext->notifyDataUpdate(key);
        }
        return nullptr;
    });
}
