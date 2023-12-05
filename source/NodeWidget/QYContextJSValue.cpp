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

bool QYContextJSValue::getBoolForKey(std::string key) {
    if (mDataMap.find(key) != mDataMap.end()) {
        return mDataMap[key]->toBoolean();
    }
    return false;
}
std::string QYContextJSValue::getStringForKey(std::string key) {
    if (mDataMap.find(key) != mDataMap.end()) {
        return mDataMap[key]->toString();
    }
    return "";
}
double QYContextJSValue::getNumberForKey(std::string key) {
    if (mDataMap.find(key) != mDataMap.end()) {
        return mDataMap[key]->toNumber();
    }
    return 0;
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
