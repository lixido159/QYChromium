//
//  QYExpressionContext.cpp
//  QYView
//
//  Created by yinquan on 2023/11/15.
//

#include "QYExpressionContext.h"

QYExpressionContext::QYExpressionContext(IQYExpDataContext *dataContext, AccessKeyCallback callback): mDataContext(dataContext), mCallback(callback) {}

QYExpressionContext::~QYExpressionContext() {
    
}

bool QYExpressionContext::getBoolForKey(std::string key) {
    if (mCallback) {
        mCallback(key);
    }
    return mDataContext->getBoolForKey(key);
}

std::string QYExpressionContext::getStringForKey(std::string key) {
    if (mCallback) {
        mCallback(key);
    }
    return mDataContext->getStringForKey(key);
}

double QYExpressionContext::getNumberForKey(std::string key) {
    if (mCallback) {
        mCallback(key);
    }
    return mDataContext->getNumberForKey(key);
}
