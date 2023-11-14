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
#include "IQYExpressionContext.h"

class QYExpression {
public:
    virtual double getNumberValue(IQYExpressionContext *expContext) = 0;
    virtual std::string getStringValue(IQYExpressionContext *expContext) = 0;
    virtual bool getBoolValue(IQYExpressionContext *expContext) = 0;
    //区分identifierExp是表达式还是固定值 red和{{ red }}
    bool isMustache = false;
};


#endif /* QYExpression_hpp */
