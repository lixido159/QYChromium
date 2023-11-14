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

void QYPageCompContext::registerDataInterface(QYJSValue *dataValue) {
    mDataValue.reset(dataValue);
    mDataValue->setFunction("update", [this](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue * {
        mData.insert(std::pair(paramsValue->getValue(0)->toString(), paramsValue->getValue(1)));
        return nullptr;
    });

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

