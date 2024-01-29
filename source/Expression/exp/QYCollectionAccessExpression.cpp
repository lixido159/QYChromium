//
//  QYCollectionAccessExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYCollectionAccessExpression.h"
QYCollectionAccessExpression::QYCollectionAccessExpression(std::shared_ptr<QYExpression> callee, std::shared_ptr<QYExpression> index): mCallee(callee), mIndex(index){}

std::shared_ptr<QYExpResult> QYCollectionAccessExpression::getExpResult(std::shared_ptr<QYExpressionContext> expContext) {
    return nullptr;
}
