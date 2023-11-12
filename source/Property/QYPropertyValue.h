//
//  QYPropertyValue.hpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#ifndef QYPropertyValue_hpp
#define QYPropertyValue_hpp
#include "QYExpression.h"
#include "IQYPropertyValueObserver.h"
#include <stdio.h>

class QYPropertyValue : public std::enable_shared_from_this<QYPropertyValue>{
public:
    QYPropertyValue(std::string key, std::string src);
    double getNumberValue();
    std::string getStringValue();
    bool getBoolValue();
    
    std::string getKey();
    
    void setObserver(std::weak_ptr<IQYPropertyValueObserver> observer);
    void onDataUpdate();
private:
    QYExpression *parseSrc(std::string src);
    
    std::string mSrc = "";
    std::string mKey = "";
    QYExpression *mExp = nullptr;
    std::weak_ptr<IQYPropertyValueObserver> mObserver;
};


#endif /* QYPropertyValue_hpp */
