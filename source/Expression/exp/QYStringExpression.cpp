//
//  QYStringExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYStringExpression.h"
QYStringExpression::QYStringExpression(std::string str): mStr(str) {}

std::shared_ptr<QYExpResult> QYStringExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    return std::make_shared<QYExpResult>(QYExpResultType::String, mStr);
}

