//
//  QYBinaryExpression.cpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#include "QYBinaryExpression.h"

QYBinaryExpression::QYBinaryExpression( std::shared_ptr<QYExpression> leftExp, std::shared_ptr<QYExpression> rightExp, OPERATOR opt):mLeftExp(leftExp), mRightExp(rightExp), mOpt(opt){
    
};


QYExpResult QYBinaryExpression::getExpResult() {
    return {QYExpResultType::None};
}
