//
//  QYNumberExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYNumberExpression_hpp
#define QYNumberExpression_hpp

#include <stdio.h>
#include "QYExpression.h"

class QYNumberExpression : public QYExpression {
public:
    QYNumberExpression(double number);
    virtual double getNumberValue(IQYExpressionContext *expContext) override;
    virtual std::string getStringValue(IQYExpressionContext *expContext) override;
    virtual bool getBoolValue(IQYExpressionContext *expContext) override;
private:
    double mNumber;
};




#endif /* QYNumberExpression_hpp */
