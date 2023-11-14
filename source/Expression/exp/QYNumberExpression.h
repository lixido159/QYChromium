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
    virtual double getNumberValue(QYExpressionContext *expContext) override;
    virtual std::string getStringValue(QYExpressionContext *expContext) override;
    virtual bool getBoolValue(QYExpressionContext *expContext) override;
private:
    double mNumber;
};




#endif /* QYNumberExpression_hpp */
