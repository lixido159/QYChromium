//
//  QYPropertyAccessExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYPropertyAccessExpression.h"

QYPropertyAccessExpression::QYPropertyAccessExpression(QYExpression *callee, std::string property) : mCallee(callee), mProperty(property){};


double QYPropertyAccessExpression::getNumberValue(IQYExpressionContext *expContext) {
    return 0;
}

std::string QYPropertyAccessExpression::getStringValue(IQYExpressionContext *expContext) {
    return "";
}

bool QYPropertyAccessExpression::getBoolValue(IQYExpressionContext *expContext) {
    return false;
}
