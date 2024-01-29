//
//  QYBinaryExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#ifndef QYBinaryExpression_hpp
#define QYBinaryExpression_hpp

#include <stdio.h>
#include "QYExpression.h"
class QYBinaryExpression : public QYExpression {
public:
    QYBinaryExpression(std::shared_ptr<QYExpression> leftExp, std::shared_ptr<QYExpression> rightExp, OPERATOR opt);
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) override;
private:
    std::shared_ptr<QYExpression> mLeftExp;
    std::shared_ptr<QYExpression> mRightExp;
    OPERATOR mOpt;
};


#endif /* QYBinaryExpression_hpp */
