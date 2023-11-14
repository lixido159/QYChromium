//
//  QYPropertyValue.cpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#include "QYPropertyValue.h"
#include <regex>
#include "QYExpressionParser.h"
QYPropertyValue::QYPropertyValue(std::string key, std::string src, std::shared_ptr<IQYExpressionContext> context):mKey(key), mSrc(src), mExpContext(context) {
    mExp = parseSrc(src);
}

QYExpression *QYPropertyValue::parseSrc(std::string src) {
    std::unique_ptr<QYExpressionParser> expParser = std::make_unique<QYExpressionParser>(src);
    return expParser->parseExp();

}



double QYPropertyValue::getNumberValue() {
    if (!mFinalValue) {
        mFinalValue = std::make_unique<QYPropertyFinalValue>(mExp->getNumberValue(mExpContext.get()));
    }
    return mFinalValue->getNumberValue();
}

std::string QYPropertyValue::getStringValue() {
    if (!mFinalValue) {
        mFinalValue = std::make_unique<QYPropertyFinalValue>(mExp->getStringValue(mExpContext.get()));
    }
    return mFinalValue->getStringValue();
}

bool QYPropertyValue::getBoolValue() {
    if (!mFinalValue) {
        mFinalValue = std::make_unique<QYPropertyFinalValue>(mExp->getBoolValue(mExpContext.get()));
    }
    return mFinalValue->getBoolValue();
}

std::string QYPropertyValue::getKey() {
    return mKey;
}

void QYPropertyValue::setObserver(std::weak_ptr<IQYPropertyValueObserver> observer) {
    mObserver = observer;
}

void QYPropertyValue::onDataUpdate() {
    auto obser = mObserver.lock();
    if (obser) {
        obser->onDataUpdate(this);
    }
}
