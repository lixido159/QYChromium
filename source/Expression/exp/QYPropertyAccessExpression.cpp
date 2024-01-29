//
//  QYPropertyAccessExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYPropertyAccessExpression.h"

QYPropertyAccessExpression::QYPropertyAccessExpression(std::shared_ptr<QYExpression> callee, std::string property) : mCallee(callee), mProperty(property){};


std::shared_ptr<QYExpResult> QYPropertyAccessExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    return nullptr;
}

