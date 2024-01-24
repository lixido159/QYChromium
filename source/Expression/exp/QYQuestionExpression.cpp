//
//  QYQuestionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYQuestionExpression.h"
QYQuestionExpression::QYQuestionExpression(std::shared_ptr<QYExpression> questionExp, std::shared_ptr<QYExpression> trueExp, std::shared_ptr<QYExpression> falseExp) : mQuestionExp(questionExp), mTrueExp(trueExp), mFalseExp(falseExp) {};

QYExpResult QYQuestionExpression::getExpResult() {
    return {QYExpResultType::None};
}


bool QYQuestionExpression::getQuestionBool() {
//    return mQuestionExp->get();
    return true;
}
