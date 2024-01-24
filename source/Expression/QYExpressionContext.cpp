//
//  QYExpressionContext.cpp
//  QYView
//
//  Created by yinquan on 2023/11/15.
//

#include "QYExpressionContext.h"

QYExpressionContext::QYExpressionContext(std::shared_ptr<IQYExpDataContext> dataContext, IQYExpressionContextObserver *observer): mDataContext(dataContext), mObserver(observer){}

QYExpressionContext::~QYExpressionContext() {
    
}

//    mObserver->expContextQueryKey(key);
//    return mDataContext->getNumberForKey(key);
