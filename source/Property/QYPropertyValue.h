//
//  QYPropertyValue.hpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#ifndef QYPropertyValue_hpp
#define QYPropertyValue_hpp
#include "QYExpression.h"
#include <stdio.h>
class QYPropertyValue {
public:
    QYPropertyValue(std::string key, std::string src);
    double getNumberValue();
    std::string getStringValue();
    bool getBoolValue();
    
    std::string getKey();
private:
    QYExpression *parseSrc(std::string src);
    
    std::string mSrc = "";
    std::string mKey = "";
    QYExpression *mExp = nullptr;
};


#endif /* QYPropertyValue_hpp */
