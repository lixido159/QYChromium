//
//  QYUnaryExpression.cpp
//  QYView
//
//  Created by yinquan on 2024/1/18.
//

#include "QYUnaryExpression.h"


QYUnaryExpression::QYUnaryExpression(std::shared_ptr<QYExpression> exp, OPERATOR opt): mExp(exp), mOpt(opt){
};


QYExpResult QYUnaryExpression::getExpResult() {
    return {QYExpResultType::None};
}
