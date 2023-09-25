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
    QYFunctionExpression(QYExpression *val, std::vector<QYExpression *> args);
    virtual double getNumberValue() override;
    virtual std::string getStringValue() override;
    virtual bool getBoolValue() override;

private:
    QYExpression *mVal;
    std::vector<QYExpression *> mArgs;
};
#endif /* QYFunctionExpression_hpp */
