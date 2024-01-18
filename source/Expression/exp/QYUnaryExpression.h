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
    QYUnaryExpression(QYExpression *exp, OPERATOR opt);
    virtual double getNumberValue(QYExpressionContext *expContext) override;
    virtual std::string getStringValue(QYExpressionContext *expContext) override;
    virtual bool getBoolValue(QYExpressionContext *expContext) override;

private:
    QYExpression *mExp;
    OPERATOR mOpt;
};


#endif /* QYUnaryExpression_hpp */
