//
//  QYIdentifierExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYIdentifierExpression.h"

QYIdentifierExpression::QYIdentifierExpression(IQYExpressionContext *context, std::string var):QYExpression(context), mVar(var) {}

double QYIdentifierExpression::getNumberValue() {
    if (!isMustache) {
        return std::stod(mVar);
    }
    return mExpContext->getNumberForKey(mVar);
}

std::string QYIdentifierExpression::getStringValue() {
    if (!isMustache) {
        return mVar;
    }
    return mExpContext->getStringForKey(mVar);
}

bool QYIdentifierExpression::getBoolValue() {
    if (!isMustache) {
        return mVar.compare("true") == 0;
    }
    return mExpContext->getBoolForKey(mVar);
}
