//
//  QYUnaryExpression.cpp
//  QYView
//
//  Created by yinquan on 2024/1/18.
//

#include "QYUnaryExpression.h"


QYUnaryExpression::QYUnaryExpression(QYExpression *exp, OPERATOR opt): mExp(exp), mOpt(opt){
};


double QYUnaryExpression::getNumberValue(QYExpressionContext *expContext){
    return 0;
}

std::string QYUnaryExpression::getStringValue(QYExpressionContext *expContext) {
    return "";
}

bool QYUnaryExpression::getBoolValue(QYExpressionContext *expContext) {
    if (mOpt == opt_not) {
        return !mExp->getBoolValue(expContext);
    }
    return false;
}

