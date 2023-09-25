//
//  QYFunctionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYFunctionExpression.h"
QYFunctionExpression::QYFunctionExpression(QYExpression *val, std::vector<QYExpression *> args): mVal(val), mArgs(args){};

double QYFunctionExpression::getNumberValue() {
    return 0;
}

std::string QYFunctionExpression::getStringValue() {
    return "";
}

bool QYFunctionExpression::getBoolValue() {
    return false;
}

