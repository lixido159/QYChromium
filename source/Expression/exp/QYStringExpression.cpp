//
//  QYStringExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYStringExpression.h"
QYStringExpression::QYStringExpression(std::string str): mStr(str) {}

double QYStringExpression::getNumberValue() {
    return std::stod(mStr);
}

std::string QYStringExpression::getStringValue() {
    return mStr;
}

bool QYStringExpression::getBoolValue() {
    return mStr.compare("true") == 0;
}
