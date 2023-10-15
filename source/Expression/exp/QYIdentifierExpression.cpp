//
//  QYIdentifierExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYIdentifierExpression.h"

QYIdentifierExpression::QYIdentifierExpression(std::string var): mVar(var) {}

double QYIdentifierExpression::getNumberValue() {
    if (!isMustache) {
        return std::stod(mVar);
    }
    return 0;
}

std::string QYIdentifierExpression::getStringValue() {
    if (!isMustache) {
        return mVar;
    }
    return "";
}

bool QYIdentifierExpression::getBoolValue() {
    if (!isMustache) {
        return mVar.compare("true") == 0;
    }
    return false;
}
