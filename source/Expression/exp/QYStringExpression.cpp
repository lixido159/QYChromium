//
//  QYStringExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYStringExpression.h"
QYStringExpression::QYStringExpression(std::string str): mStr(str) {}

double QYStringExpression::getNumberValue(IQYExpressionContext *expContext) {
    return std::stod(mStr);
}

std::string QYStringExpression::getStringValue(IQYExpressionContext *expContext) {
    return mStr;
}

bool QYStringExpression::getBoolValue(IQYExpressionContext *expContext) {
    return mStr.compare("true") == 0;
}
