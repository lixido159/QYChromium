//
//  QYPageCompContext.cpp
//  QYView
//
//  Created by yinquan on 2023/11/9.
//

#include "QYPageCompContext.h"
#include "QYPropertyValue.h"

QYPageCompContext::QYPageCompContext(std::shared_ptr<QYJSContext> jsContext) {
    mJSContext = jsContext;
}

void QYPageCompContext::addJSKeyObserver(std::string key, std::shared_ptr<QYPropertyValue> observer) {
    //说明该key还没有属性监听
    if (mObserveProperties.find(key) == mObserveProperties.end()) {
        std::vector<std::shared_ptr<QYPropertyValue>> obs = {observer};
        mObserveProperties.insert(std::pair(key, obs));
    } else {
        std::vector<std::shared_ptr<QYPropertyValue>> obs = mObserveProperties[key];
        obs.push_back(observer);
    }
}

void QYPageCompContext::notifyDataUpdate(std::string key) {
    std::vector<std::shared_ptr<QYPropertyValue>> obs = mObserveProperties[key];
    for (int i = 0; i < obs.size(); i++) {
        std::shared_ptr<QYPropertyValue> proptyValue = obs[i];
        proptyValue->onDataUpdate();
        
    }
}

void QYPageCompContext::registerDataInterface(QYJSValue *dataValue) {
    mDataValue.reset(dataValue);
    mDataValue->setFunction("update", [this](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue * {
        std::string key = paramsValue->getValue(0)->toString();
        auto iter = mData.find(key);
        if (iter != mData.end()) {
            mData.erase(iter);
        }
        mData.insert(std::pair(key, paramsValue->getValue(1)));
        notifyDataUpdate(key);
        return nullptr;
    });
}

void QYPageCompContext::setPageCompValue(QYJSValue *value) {
    mPageCompJSValue.reset(value);
}

QYJSValue* QYPageCompContext::getPageCompValue() {
    return mPageCompJSValue.get();
}

std::shared_ptr<QYJSContext> QYPageCompContext::getJSContext() {
    return mJSContext;
}

bool QYPageCompContext::getBoolForKey(std::string key) {
    if (mData.find(key) != mData.end()) {
        return mData[key]->toBoolean();
    }
    return false;
}
std::string QYPageCompContext::getStringForKey(std::string key) {
    if (mData.find(key) != mData.end()) {
        return mData[key]->toString();
    }
    return "";
}
double QYPageCompContext::getNumberForKey(std::string key) {
    if (mData.find(key) != mData.end()) {
        return mData[key]->toNumber();
    }
    return 0;
}

