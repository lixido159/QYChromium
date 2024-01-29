//
//  QYQuestionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYQuestionExpression.h"
QYQuestionExpression::QYQuestionExpression(std::shared_ptr<QYExpression> questionExp, std::shared_ptr<QYExpression> trueExp, std::shared_ptr<QYExpression> falseExp) : mQuestionExp(questionExp), mTrueExp(trueExp), mFalseExp(falseExp) {};

std::shared_ptr<QYExpResult> QYQuestionExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext)
{
    bool isTrue = mQuestionExp->getExpResult(expContext)->getBoolean();
    return isTrue ? mTrueExp->getExpResult(expContext) : mFalseExp->getExpResult(expContext);
}
