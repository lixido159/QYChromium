//
//  QYFunctionExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#include "QYFunctionExpression.h"
QYFunctionExpression::QYFunctionExpression(std::shared_ptr<QYExpression> val, std::vector<std::shared_ptr<QYExpression> > args): mVal(val), mArgs(args){};

QYExpResult QYFunctionExpression::getExpResult() {
    return {QYExpResultType::None};
}
