//
//  QYExpressionContext.hpp
//  QYView
//
//  Created by yinquan on 2023/11/15.
//

#ifndef QYExpressionContext_hpp
#define QYExpressionContext_hpp

#include <stdio.h>
#include <string>
#include "IQYExpDataContext.h"

class IQYExpressionContextObserver {
public:
    virtual void expContextQueryKey(std::string key) = 0;
};

class QYExpressionContext {
public:
    QYExpressionContext(std::shared_ptr<IQYExpDataContext> dataContext, IQYExpressionContextObserver *observer);
    ~QYExpressionContext();
private:
    std::shared_ptr<IQYExpDataContext> mDataContext;
    IQYExpressionContextObserver *mObserver;
};

#endif /* QYExpressionContext_hpp */
