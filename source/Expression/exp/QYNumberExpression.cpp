//
//  QYNumberExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYNumberExpression.h"


QYNumberExpression::QYNumberExpression(double number):mNumber(number){};


std::shared_ptr<QYExpResult> QYNumberExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    return std::make_shared<QYExpResult>(QYExpResultType::Number, mNumber);
}
