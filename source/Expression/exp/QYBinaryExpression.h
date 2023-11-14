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
    QYBinaryExpression(IQYExpressionContext *context, QYExpression *leftExp, QYExpression *rightExp, OPERATOR opt);
    virtual double getNumberValue() override;
    virtual std::string getStringValue() override;
    virtual bool getBoolValue() override;

private:
    QYExpression *mLeftExp;
    QYExpression *mRightExp;
    OPERATOR mOpt;
};


#endif /* QYBinaryExpression_hpp */
