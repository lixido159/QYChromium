//
//  QYExpression.hpp
//  QYView
//
//  Created by yinquan on 2023/9/25.
//

#ifndef QYExpression_hpp
#define QYExpression_hpp

#include <stdio.h>
#include <string>
#include "QYToken.h"


class QYExpression {
public:
    virtual double getNumberValue() = 0;
    virtual std::string getStringValue() = 0;
    virtual bool getBoolValue() = 0;
};


#endif /* QYExpression_hpp */
