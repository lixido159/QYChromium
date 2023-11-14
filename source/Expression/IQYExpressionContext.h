//
//  QYExpressionContext.hpp
//  QYView
//
//  Created by yinquan on 2023/11/13.
//

#ifndef QYExpressionContext_hpp
#define QYExpressionContext_hpp

#include <stdio.h>

class IQYExpressionContext {
public:
    virtual bool getBoolForKey(std::string key) = 0;
    virtual std::string getStringForKey(std::string key) = 0;
    virtual double getNumberForKey(std::string key) = 0;
};

#endif /* QYExpressionContext_hpp */
