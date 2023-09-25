//
//  QYPropertyAccessExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYPropertyAccessExpression.h"

QYPropertyAccessExpression::QYPropertyAccessExpression(QYExpression *callee, std::string property) : mCallee(callee), mProperty(property){};


double QYPropertyAccessExpression::getNumberValue() {
    return 0;
}

std::string QYPropertyAccessExpression::getStringValue() {
    return "";
}

bool QYPropertyAccessExpression::getBoolValue() {
    return false;
}
