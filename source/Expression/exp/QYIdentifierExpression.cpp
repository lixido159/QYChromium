//
//  QYIdentifierExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYIdentifierExpression.h"

QYIdentifierExpression::QYIdentifierExpression(std::string var): mVar(var) {}

double QYIdentifierExpression::getNumberValue(IQYExpressionContext *expContext) {
    if (!isMustache) {
        return std::stod(mVar);
    }
    return expContext->getNumberForKey(mVar);
}

std::string QYIdentifierExpression::getStringValue(IQYExpressionContext *expContext) {
    if (!isMustache) {
        return mVar;
    }
    return expContext->getStringForKey(mVar);
}

bool QYIdentifierExpression::getBoolValue(IQYExpressionContext *expContext) {
    if (!isMustache) {
        return mVar.compare("true") == 0;
    }
    return expContext->getBoolForKey(mVar);
}
