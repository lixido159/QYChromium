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
    virtual double getNumberValue(IQYExpressionContext *expContext) override;
    virtual std::string getStringValue(IQYExpressionContext *expContext) override;
    virtual bool getBoolValue(IQYExpressionContext *expContext) override;

private:
    QYExpression *mLeftExp;
    QYExpression *mRightExp;
    OPERATOR mOpt;
};


#endif /* QYBinaryExpression_hpp */
