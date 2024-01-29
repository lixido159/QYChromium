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
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) override;
private:
    std::string mVar;
};


#endif /* QYIdentifierExpression_hpp */
