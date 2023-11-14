//
//  QYStringExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYStringExpression_hpp
#define QYStringExpression_hpp

#include <stdio.h>
#include "QYExpression.h"
#endif /* QYStringExpression_hpp */
class QYStringExpression : public QYExpression {
public:
    QYStringExpression(std::string str);
    
    virtual double getNumberValue(QYExpressionContext *expContext) override;
    virtual std::string getStringValue(QYExpressionContext *expContext) override;
    virtual bool getBoolValue(QYExpressionContext *expContext) override;
private:
    std::string mStr;    
};
