//
//  QYPropertyValue.cpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#include "QYPropertyValue.h"
#include <regex>
#include "QYExpressionParser.h"
QYPropertyValue::QYPropertyValue(std::string key, std::string src, std::shared_ptr<QYPageCompContext> pageCompContext):mKey(key), mSrc(src), mPageCompContext(pageCompContext) {
}

QYPropertyValue::~QYPropertyValue() {
    
}

std::shared_ptr<QYExpression> QYPropertyValue::parseSrc(std::string src) {
    std::unique_ptr<QYExpressionParser> expParser = std::make_unique<QYExpressionParser>(src);

    return expParser->parseExp();

}

std::shared_ptr<QYExpResult> QYPropertyValue::getResult() {
    if (!mResult) {
        
        mResult = getExpression()->getExpResult(std::make_shared<QYExpressionContext>(mPageCompContext->getContextJSValue(), shared_from_this()));
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
    mResult = nullptr;
}

void QYPropertyValue::onDataUpdate(std::string key) {
    clear();
    mObserver->onDataUpdate(shared_from_this());
}

void QYPropertyValue::expContextQueryKey(std::string key) {
    mPageCompContext->addJSKeyObserver(key, shared_from_this());
}

std::shared_ptr<QYExpression> QYPropertyValue::getExpression() {
    if (!mExp) {
        mExp = parseSrc(mSrc);
    }
    return mExp;
}
