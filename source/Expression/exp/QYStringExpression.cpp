//
//  QYStringExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYStringExpression.h"
QYStringExpression::QYStringExpression(std::string str): mStr(str) {}

QYExpResult QYStringExpression::getExpResult() {
    return {QYExpResultType::String, .string = mStr};
}

