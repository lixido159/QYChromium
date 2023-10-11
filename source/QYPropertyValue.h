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
    QYPropertyValue(std::string src);
    
private:
    QYExpression *parseSrc(std::string src);
    
    std::string mSrc = "";
    QYExpression *mExp = nullptr;
};


#endif /* QYPropertyValue_hpp */
