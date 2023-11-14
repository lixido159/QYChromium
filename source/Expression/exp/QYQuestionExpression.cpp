//
//  QYQuestionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYQuestionExpression.h"
QYQuestionExpression::QYQuestionExpression(QYExpression *questionExp, QYExpression *trueExp, QYExpression *falseExp) : mQuestionExp(questionExp), mTrueExp(trueExp), mFalseExp(falseExp) {};

double QYQuestionExpression::getNumberValue(QYExpressionContext *expContext) {
    if (getQuestionBool(expContext)) {
        return mTrueExp->getNumberValue(expContext);
    } else {
        return mFalseExp->getNumberValue(expContext);
    }
}

std::string QYQuestionExpression::getStringValue(QYExpressionContext *expContext) {
    if (getQuestionBool(expContext)) {
        return mTrueExp->getStringValue(expContext);
    } else {
        return mFalseExp->getStringValue(expContext);
    }
}

bool QYQuestionExpression::getBoolValue(QYExpressionContext *expContext) {
    if (getQuestionBool(expContext)) {
        return mTrueExp->getBoolValue(expContext);
    } else {
        return mFalseExp->getBoolValue(expContext);
    }
}

bool QYQuestionExpression::getQuestionBool(QYExpressionContext *expContext) {
    return mQuestionExp->getBoolValue(expContext);
}
