//
//  QYPageCompContext.cpp
//  QYView
//
//  Created by yinquan on 2023/11/9.
//

#include "QYPageCompContext.h"
#include "QYPropertyValue.h"

QYPageCompContext::QYPageCompContext(std::shared_ptr<QYJSContext> jsContext):mJSContext(jsContext) {
}

void QYPageCompContext::init() {
    mContextJSValue = std::make_shared<QYContextJSValue>(weak_from_this());
}

void QYPageCompContext::addJSKeyObserver(std::string key, std::shared_ptr<IQYPageCompDataObserver> observer) {
    //说明该key还没有属性监听
    if (mDataObservers.find(key) == mDataObservers.end()) {
        std::vector<std::shared_ptr<IQYPageCompDataObserver>> obs = {observer};
        mDataObservers.insert(std::pair(key, obs));
    } else {
        std::vector<std::shared_ptr<IQYPageCompDataObserver>> &obs = mDataObservers[key];
        obs.push_back(observer);
    }
}

void QYPageCompContext::notifyDataUpdate(std::string key) {
    std::vector<std::shared_ptr<IQYPageCompDataObserver>> obs = mDataObservers[key];
    for (int i = 0; i < obs.size(); i++) {
        std::shared_ptr<IQYPageCompDataObserver> proptyValue = obs[i];
        proptyValue->onDataUpdate(key);
        
    }
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

std::shared_ptr<QYContextJSValue> QYPageCompContext::getContextJSValue() {
    return mContextJSValue;
}


