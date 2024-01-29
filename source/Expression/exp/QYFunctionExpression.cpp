//
//  QYFunctionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYFunctionExpression.h"
QYFunctionExpression::QYFunctionExpression(std::shared_ptr<QYExpression> val, std::vector<std::shared_ptr<QYExpression> > args): mVal(val), mArgs(args){};

std::shared_ptr<QYExpResult> QYFunctionExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    return nullptr;
}
