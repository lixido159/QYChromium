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
    virtual QYExpResult getExpResult() override;
private:
    double mNumber;
};




#endif /* QYNumberExpression_hpp */
