//
//  QYIdentifierExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYIdentifierExpression.h"

QYIdentifierExpression::QYIdentifierExpression(std::string var): mVar(var) {}

double QYIdentifierExpression::getNumberValue() {
    return 0;
}

std::string QYIdentifierExpression::getStringValue() {
    return "";
}

bool QYIdentifierExpression::getBoolValue() {
    return false;
}
