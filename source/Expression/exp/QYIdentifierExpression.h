//
//  QYIdentifierExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYIdentifierExpression_hpp
#define QYIdentifierExpression_hpp

#include <stdio.h>
#include "QYExpression.h"


class QYIdentifierExpression : public QYExpression{
public:
    QYIdentifierExpression(std::string var);
    virtual double getNumberValue() override;
    virtual std::string getStringValue() override;
    virtual bool getBoolValue() override;

private:
    std::string mVar;
};


#endif /* QYIdentifierExpression_hpp */