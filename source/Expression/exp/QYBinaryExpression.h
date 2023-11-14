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
    QYBinaryExpression(QYExpression *leftExp, QYExpression *rightExp, OPERATOR opt);
    virtual double getNumberValue(QYExpressionContext *expContext) override;
    virtual std::string getStringValue(QYExpressionContext *expContext) override;
    virtual bool getBoolValue(QYExpressionContext *expContext) override;

private:
    QYExpression *mLeftExp;
    QYExpression *mRightExp;
    OPERATOR mOpt;
};


#endif /* QYBinaryExpression_hpp */
