//
//  QYFunctionExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYFunctionExpression_hpp
#define QYFunctionExpression_hpp

#include <stdio.h>
#include "QYExpression.h"
class QYFunctionExpression : public QYExpression{
public:
    QYFunctionExpression(std::shared_ptr<QYExpression> val, std::vector<std::shared_ptr<QYExpression> > args);
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) override;
private:
    std::shared_ptr<QYExpression> mVal;
    std::vector<std::shared_ptr<QYExpression> > mArgs;
};
#endif /* QYFunctionExpression_hpp */
