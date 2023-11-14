//
//  QYPropertyAccessExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#ifndef QYPropertyAccessExpression_hpp
#define QYPropertyAccessExpression_hpp

#include <stdio.h>
#include "QYExpression.h"
class QYPropertyAccessExpression : public QYExpression{
public:
    QYPropertyAccessExpression(QYExpression *callee, std::string property);
    virtual double getNumberValue(IQYExpressionContext *expContext) override;
    virtual std::string getStringValue(IQYExpressionContext *expContext) override;
    virtual bool getBoolValue(IQYExpressionContext *expContext) override;

private:
    QYExpression *mCallee;
    std::string mProperty;
};
#endif /* QYPropertyAccessExpression_hpp */
