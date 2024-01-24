//
//  QYIdentifierExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYIdentifierExpression.h"

QYIdentifierExpression::QYIdentifierExpression(std::string var): mVar(var) {}


QYExpResult QYIdentifierExpression::getExpResult() {
    return mExpContext->getResultForKey(mVar);
}

