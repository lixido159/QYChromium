//
//  QYBinaryExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYBinaryExpression.h"

QYBinaryExpression::QYBinaryExpression(IQYExpressionContext *context, QYExpression *leftExp, QYExpression *rightExp, OPERATOR opt):QYExpression(context), mLeftExp(leftExp), mRightExp(rightExp), mOpt(opt){};


double QYBinaryExpression::getNumberValue(){
    switch(mOpt) {
        case opt_add:
            return mLeftExp->getNumberValue() + mRightExp->getNumberValue();
        case opt_sub:
            return mLeftExp->getNumberValue() - mRightExp->getNumberValue();
        case opt_mul:
            return mLeftExp->getNumberValue() * mRightExp->getNumberValue();
        case opt_div:
            return mLeftExp->getNumberValue() / mRightExp->getNumberValue();
        default:
            throw "错误符号进行计算";
    }

    return mLeftExp->getNumberValue();
}

std::string QYBinaryExpression::getStringValue() {
    return "";
}

bool QYBinaryExpression::getBoolValue() {
    return getNumberValue() > 0;
}
