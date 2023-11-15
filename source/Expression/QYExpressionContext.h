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
    QYExpressionContext(IQYExpDataContext *dataContext, IQYExpressionContextObserver *observer);
    ~QYExpressionContext();
    bool getBoolForKey(std::string key);
    std::string getStringForKey(std::string key);
    double getNumberForKey(std::string key);
private:
    IQYExpDataContext *mDataContext;
    IQYExpressionContextObserver *mObserver;
};

#endif /* QYExpressionContext_hpp */
