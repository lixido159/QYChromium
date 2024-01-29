//
//  QYUnaryExpression.cpp
//  QYView
//
//  Created by yinquan on 2024/1/18.
//

#include "QYUnaryExpression.h"


QYUnaryExpression::QYUnaryExpression(std::shared_ptr<QYExpression> exp, OPERATOR opt): mExp(exp), mOpt(opt){
};


std::shared_ptr<QYExpResult> QYUnaryExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    if (mOpt == opt_not) {
        std::shared_ptr<QYExpResult> result = mExp->getExpResult(expContext);
        return std::make_shared<QYExpResult>(QYExpResultType::Boolean, !result->getBoolean());
    }
    return std::make_shared<QYExpResult>();
}
