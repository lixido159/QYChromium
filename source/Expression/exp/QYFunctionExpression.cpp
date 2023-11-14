//
//  QYFunctionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYFunctionExpression.h"
QYFunctionExpression::QYFunctionExpression(QYExpression *val, std::vector<QYExpression *> args): mVal(val), mArgs(args){};

double QYFunctionExpression::getNumberValue(IQYExpressionContext *expContext) {
    return 0;
}

std::string QYFunctionExpression::getStringValue(IQYExpressionContext *expContext) {
    return "";
}

bool QYFunctionExpression::getBoolValue(IQYExpressionContext *expContext) {
    return false;
}

