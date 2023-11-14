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
typedef void (*AccessKeyCallback)(std::string key);
class QYExpressionContext {
public:
    QYExpressionContext(IQYExpDataContext *dataContext, AccessKeyCallback callback);
    ~QYExpressionContext();
    bool getBoolForKey(std::string key);
    std::string getStringForKey(std::string key);
    double getNumberForKey(std::string key);
private:
    IQYExpDataContext *mDataContext;
    AccessKeyCallback mCallback;
};

#endif /* QYExpressionContext_hpp */
