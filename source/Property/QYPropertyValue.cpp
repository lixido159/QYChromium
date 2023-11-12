//
//  QYPropertyValue.cpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#include "QYPropertyValue.h"
#include <regex>
#include "QYExpressionParser.h"
QYPropertyValue::QYPropertyValue(std::string key, std::string src):mKey(key), mSrc(src) {
    mExp = parseSrc(src);
}

QYExpression *QYPropertyValue::parseSrc(std::string src) {
    std::unique_ptr<QYExpressionParser> expParser = std::make_unique<QYExpressionParser>(src);
    return expParser->parseExp();

}

double QYPropertyValue::getNumberValue() {
    return mExp->getNumberValue();
}

std::string QYPropertyValue::getStringValue() {
    return mExp->getStringValue();
}

bool QYPropertyValue::getBoolValue() {
    return mExp->getBoolValue();
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
