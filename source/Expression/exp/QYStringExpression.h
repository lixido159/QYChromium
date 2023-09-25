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
    
    virtual double getNumberValue() override;
    virtual std::string getStringValue() override;
    virtual bool getBoolValue() override;
private:
    std::string mStr;    
};
