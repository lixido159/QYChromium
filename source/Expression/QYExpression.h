//
//  QYExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYExpression_hpp
#define QYExpression_hpp

#include <stdio.h>
#include <string>
#include "QYToken.h"
#include "QYExpressionContext.h"



class QYExpression {
public:
    virtual QYExpResult getExpResult() = 0;
    //区分identifierExp是表达式还是固定值 red和{{ red }}
    bool isMustache = false;
public:
    void setContext(std::shared_ptr<IQYExpDataContext> context);
protected:
    std::shared_ptr<IQYExpDataContext> mExpContext;
};

std::string to_string_precise(double value);

#endif /* QYExpression_hpp */
