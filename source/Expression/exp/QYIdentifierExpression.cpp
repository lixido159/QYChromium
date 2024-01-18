//
//  QYIdentifierExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYIdentifierExpression.h"

QYIdentifierExpression::QYIdentifierExpression(std::string var): mVar(var) {}

double QYIdentifierExpression::getNumberValue(QYExpressionContext *expContext) {
    return expContext->getNumberForKey(mVar);
}

std::string QYIdentifierExpression::getStringValue(QYExpressionContext *expContext) {
    return expContext->getStringForKey(mVar);
}

bool QYIdentifierExpression::getBoolValue(QYExpressionContext *expContext) {
    return expContext->getBoolForKey(mVar);
}
