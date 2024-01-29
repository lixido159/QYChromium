//
//  QYExpressionContext.cpp
//  QYView
//
//  Created by yinquan on 2023/11/15.
//

#include "QYExpressionContext.h"

QYExpressionContext::QYExpressionContext(std::shared_ptr<IQYExpDataContext> dataContext, std::shared_ptr<IQYExpressionContextObserver> observer): mDataContext(dataContext), mObserver(observer){}

QYExpressionContext::~QYExpressionContext() {
    
}

std::shared_ptr<QYExpResult> QYExpressionContext::getResultForKey(std::string key) {
    mObserver->expContextQueryKey(key);
    return mDataContext->getResultForKey(key);

}
