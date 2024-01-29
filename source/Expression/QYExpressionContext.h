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
    QYExpressionContext(std::shared_ptr<IQYExpDataContext> dataContext, std::shared_ptr<IQYExpressionContextObserver> observer);
    ~QYExpressionContext();
    std::shared_ptr<QYExpResult> getResultForKey(std::string key);
private:
    std::shared_ptr<IQYExpDataContext> mDataContext;
    std::shared_ptr<IQYExpressionContextObserver> mObserver;
};

#endif /* QYExpressionContext_hpp */
