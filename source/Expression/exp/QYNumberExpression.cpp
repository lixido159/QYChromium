//
//  QYNumberExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYNumberExpression.h"


QYNumberExpression::QYNumberExpression(double number):mNumber(number){};


QYExpResult QYNumberExpression::getExpResult() {
    return {QYExpResultType::Number, .number = mNumber};
}
