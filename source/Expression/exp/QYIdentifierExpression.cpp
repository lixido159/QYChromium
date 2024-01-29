//
//  QYIdentifierExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYIdentifierExpression.h"

QYIdentifierExpression::QYIdentifierExpression(std::string var): mVar(var) {}


std::shared_ptr<QYExpResult> QYIdentifierExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    return expContext->getResultForKey(mVar);
}

