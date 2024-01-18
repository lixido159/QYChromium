//
//  QYNumberExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYNumberExpression.h"


QYNumberExpression::QYNumberExpression(double number):mNumber(number){};

double QYNumberExpression::getNumberValue(QYExpressionContext *expContext) {
    return mNumber;
}

std::string QYNumberExpression::getStringValue(QYExpressionContext *expContext) {
    return to_string_precise(mNumber);
}

bool QYNumberExpression::getBoolValue(QYExpressionContext *expContext) {
    return mNumber > 0;
}
