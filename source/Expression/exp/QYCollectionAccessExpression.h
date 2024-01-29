//
//  QYCollectionAccessExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/26.
//

#ifndef QYCollectionAccessExpression_hpp
#define QYCollectionAccessExpression_hpp

#include <stdio.h>
#include "QYExpression.h"
class QYCollectionAccessExpression : public QYExpression{
public:
    QYCollectionAccessExpression(std::shared_ptr<QYExpression> callee, std::shared_ptr<QYExpression> index);
    std::shared_ptr<QYExpression> mCallee;
    //数组、字典都有可能
    std::shared_ptr<QYExpression> mIndex;
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) override;
};

#endif /* QYCollectionAccessExpression_hpp */
