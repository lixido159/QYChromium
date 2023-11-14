//
//  QYPageCompContext.cpp
//  QYView
//
//  Created by yinquan on 2023/11/9.
//

#include "QYPageCompContext.h"
#include "QYPropertyValue.h"

void QYPageCompContext::addProptyObserver(std::weak_ptr<QYPropertyValue> observer) {
    //防止重复添加
    if (std::find_if(mObserveProperties.begin(), mObserveProperties.end(), [observer](std::weak_ptr<QYPropertyValue> a) {
        return a.lock() == observer.lock();
    }) == mObserveProperties.end()) {
        mObserveProperties.push_back(observer);
    }
}

void QYPageCompContext::notifyDataUpdate() {
    for (int i = 0; i < mObserveProperties.size(); i++) {
        std::weak_ptr<QYPropertyValue> proptyValue = mObserveProperties[0];
        auto value = proptyValue.lock();
        if (value) {
            value->onDataUpdate();
        }
    }
}

void QYPageCompContext::setDataValue(std::shared_ptr<QYJSValue> dataValue) {
    mDataValue = dataValue;
}

bool QYPageCompContext::getBoolForKey(std::string key) {
    return mDataValue->getValue(key)->toBoolean();
}
std::string QYPageCompContext::getStringForKey(std::string key) {
    return mDataValue->getValue(key)->toString();
}
double QYPageCompContext::getNumberForKey(std::string key) {
    return mDataValue->getValue(key)->toNumber();
}

