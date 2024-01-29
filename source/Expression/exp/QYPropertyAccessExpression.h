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
    QYPropertyAccessExpression(std::shared_ptr<QYExpression> callee, std::string property);
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) override;
private:
    std::shared_ptr<QYExpression> mCallee;
    std::string mProperty;
};
#endif /* QYPropertyAccessExpression_hpp */
