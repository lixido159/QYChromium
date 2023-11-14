//
//  QYBinaryExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYBinaryExpression.h"

QYBinaryExpression::QYBinaryExpression( QYExpression *leftExp, QYExpression *rightExp, OPERATOR opt):mLeftExp(leftExp), mRightExp(rightExp), mOpt(opt){};


double QYBinaryExpression::getNumberValue(IQYExpressionContext *expContext){
    switch(mOpt) {
        case opt_add:
            return mLeftExp->getNumberValue(expContext) + mRightExp->getNumberValue(expContext);
        case opt_sub:
            return mLeftExp->getNumberValue(expContext) - mRightExp->getNumberValue(expContext);
        case opt_mul:
            return mLeftExp->getNumberValue(expContext) * mRightExp->getNumberValue(expContext);
        case opt_div:
            return mLeftExp->getNumberValue(expContext) / mRightExp->getNumberValue(expContext);
        default:
            throw "错误符号进行计算";
    }

    return mLeftExp->getNumberValue(expContext);
}

std::string QYBinaryExpression::getStringValue(IQYExpressionContext *expContext) {
    return "";
}

bool QYBinaryExpression::getBoolValue(IQYExpressionContext *expContext) {
    return getNumberValue(expContext) > 0;
}
