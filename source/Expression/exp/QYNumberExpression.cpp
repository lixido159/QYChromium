//
//  QYNumberExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYNumberExpression.h"


QYNumberExpression::QYNumberExpression(double number):mNumber(number){};

double QYNumberExpression::getNumberValue(IQYExpressionContext *expContext) {
    return mNumber;
}

std::string QYNumberExpression::getStringValue(IQYExpressionContext *expContext) {
    return std::to_string(mNumber);
}

bool QYNumberExpression::getBoolValue(IQYExpressionContext *expContext) {
    return mNumber > 0;
}
