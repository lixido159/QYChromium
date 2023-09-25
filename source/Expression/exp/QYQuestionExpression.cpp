//
//  QYQuestionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYQuestionExpression.h"
QYQuestionExpression::QYQuestionExpression(QYExpression *questionExp, QYExpression *trueExp, QYExpression *falseExp) : mQuestionExp(questionExp), mTrueExp(trueExp), mFalseExp(falseExp) {};

double QYQuestionExpression::getNumberValue() {
    if (getQuestionBool()) {
        return mTrueExp->getNumberValue();
    } else {
        return mFalseExp->getNumberValue();
    }
}

std::string QYQuestionExpression::getStringValue() {
    if (getQuestionBool()) {
        return mTrueExp->getStringValue();
    } else {
        return mFalseExp->getStringValue();
    }
}

bool QYQuestionExpression::getBoolValue() {
    if (getQuestionBool()) {
        return mTrueExp->getBoolValue();
    } else {
        return mFalseExp->getBoolValue();
    }
}

bool QYQuestionExpression::getQuestionBool() {
    return mQuestionExp->getBoolValue();
}
