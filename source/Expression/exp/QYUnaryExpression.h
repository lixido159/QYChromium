//
//  QYUnaryExpression.hpp
//  QYView
//
//  Created by yinquan on 2024/1/18.
//

#ifndef QYUnaryExpression_hpp
#define QYUnaryExpression_hpp

#include <stdio.h>
#include "QYExpression.h"

class QYUnaryExpression : public QYExpression {
public:
    QYUnaryExpression(std::shared_ptr<QYExpression> exp, OPERATOR opt);
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) override;
    
private:
    std::shared_ptr<QYExpression> mExp;
    OPERATOR mOpt;
};


#endif /* QYUnaryExpression_hpp */
