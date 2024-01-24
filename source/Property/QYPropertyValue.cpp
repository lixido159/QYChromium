//
//  QYPropertyValue.cpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#include "QYPropertyValue.h"
#include <regex>
#include "QYExpressionParser.h"
QYPropertyValue::QYPropertyValue(std::string key, std::string src, std::shared_ptr<QYPageCompContext> dataContext):mKey(key), mSrc(src), mDataContext(dataContext) {
}

QYPropertyValue::~QYPropertyValue() {
    
}

std::shared_ptr<QYExpression> QYPropertyValue::parseSrc(std::string src) {
    std::unique_ptr<QYExpressionParser> expParser = std::make_unique<QYExpressionParser>(getExpContext(), src);

    return expParser->parseExp();

}

QYExpResult QYPropertyValue::getResult() {
    if (!mResult) {
        mResult = getExpression()->getExpResult();
    }
    return mResult;

}

std::string QYPropertyValue::getKey() {
    return mKey;
}

std::string QYPropertyValue::getSrc() {
    return mSrc;
}

void QYPropertyValue::setObserver(IQYPropertyValueObserver *observer) {
    mObserver = observer;
}

//当属性更新时
void QYPropertyValue::clear() {
    mFinalValue = nullptr;
}

void QYPropertyValue::onDataUpdate() {
    clear();
    mObserver->onDataUpdate(shared_from_this());
}

void QYPropertyValue::expContextQueryKey(std::string key) {
    mDataContext->addJSKeyObserver(key, shared_from_this());
}

std::shared_ptr<QYExpressionContext> QYPropertyValue::getExpContext() {
    if (!mExpContext) {
        mExpContext = std::make_unique<QYExpressionContext>(mDataContext->getContextJSValue(), this);
    }
    return mExpContext;
}

std::shared_ptr<QYExpression> QYPropertyValue::getExpression() {
    if (!mExp) {
        mExp = parseSrc(src);

    }
    return mExp;
}
