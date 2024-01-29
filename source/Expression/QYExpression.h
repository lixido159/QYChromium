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
#include "QYExpResult.h"
#include "IQYExpDataContext.h"
#include "QYExpressionContext.h"


class QYExpression {
public:
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) = 0;
    //区分identifierExp是表达式还是固定值 red和{{ red }}
    bool isMustache = false;
};

std::string to_string_precise(double value);
QYExpResult calculateBinaryExp(QYExpression *first, QYExpression *second, OPERATOR opt);

#endif /* QYExpression_hpp */
