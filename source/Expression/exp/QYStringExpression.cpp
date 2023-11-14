//
//  QYStringExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYStringExpression.h"
QYStringExpression::QYStringExpression(std::string str): mStr(str) {}

double QYStringExpression::getNumberValue(QYExpressionContext *expContext) {
    return std::stod(mStr);
}

std::string QYStringExpression::getStringValue(QYExpressionContext *expContext) {
    return mStr;
}

bool QYStringExpression::getBoolValue(QYExpressionContext *expContext) {
    return mStr.compare("true") == 0;
}
