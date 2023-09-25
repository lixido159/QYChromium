//
//  QYNumberExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYNumberExpression.h"


QYNumberExpression::QYNumberExpression(double number):mNumber(number){};

double QYNumberExpression::getNumberValue() {
    return mNumber;
}

std::string QYNumberExpression::getStringValue() {
    return std::to_string(mNumber);
}

bool QYNumberExpression::getBoolValue() {
    return mNumber > 0;
}
