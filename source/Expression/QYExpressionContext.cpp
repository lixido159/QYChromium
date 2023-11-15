//
//  QYExpressionContext.cpp
//  QYView
//
//  Created by yinquan on 2023/11/15.
//

#include "QYExpressionContext.h"

QYExpressionContext::QYExpressionContext(IQYExpDataContext *dataContext, IQYExpressionContextObserver *observer): mDataContext(dataContext), mObserver(observer){}

QYExpressionContext::~QYExpressionContext() {
    
}

bool QYExpressionContext::getBoolForKey(std::string key) {
    mObserver->expContextQueryKey(key);
    return mDataContext->getBoolForKey(key);
}

std::string QYExpressionContext::getStringForKey(std::string key) {
    mObserver->expContextQueryKey(key);
    return mDataContext->getStringForKey(key);
}

double QYExpressionContext::getNumberForKey(std::string key) {
    mObserver->expContextQueryKey(key);
    return mDataContext->getNumberForKey(key);
}
