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
    virtual std::shared_ptr<QYExpResult> getExpResult(std::shared_ptr<QYExpressionContext> expContext) override;
private:
    std::string mStr;    
};
