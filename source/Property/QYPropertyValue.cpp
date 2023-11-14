//
//  QYPropertyValue.cpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#include "QYPropertyValue.h"
#include <regex>
#include "QYExpressionParser.h"
QYPropertyValue::QYPropertyValue(std::string key, std::string src, std::shared_ptr<IQYExpDataContext> dataContext):mKey(key), mSrc(src), mDataContext(dataContext) {
    mExp = parseSrc(src);
}

QYPropertyValue::~QYPropertyValue() {
    
}

QYExpression *QYPropertyValue::parseSrc(std::string src) {
    std::unique_ptr<QYExpressionParser> expParser = std::make_unique<QYExpressionParser>(src);
    return expParser->parseExp();

}


double QYPropertyValue::getNumberValue() {
    if (!mFinalValue) {
        std::unique_ptr<QYExpressionContext> expContext = std::make_unique<QYExpressionContext>(mDataContext, [](std::string key)->void {
            
        });
        mFinalValue = std::make_unique<QYPropertyFinalValue>(mExp->getNumberValue(expContext.get()));
    }
    return mFinalValue->getNumberValue();
}

std::string QYPropertyValue::getStringValue() {
    if (!mFinalValue) {
        std::unique_ptr<QYExpressionContext> expContext = std::make_unique<QYExpressionContext>(mDataContext, [](std::string key)->void {
            
        });
        mFinalValue = std::make_unique<QYPropertyFinalValue>(mExp->getStringValue(expContext.get()));
    }
    return mFinalValue->getStringValue();
}

bool QYPropertyValue::getBoolValue() {
    if (!mFinalValue) {
        std::unique_ptr<QYExpressionContext> expContext = std::make_unique<QYExpressionContext>(mDataContext, [](std::string key)->void {
            
        });
        mFinalValue = std::make_unique<QYPropertyFinalValue>(mExp->getBoolValue(expContext.get()));
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
