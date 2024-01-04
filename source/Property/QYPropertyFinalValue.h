//
//  QYPropertyFinalValue.hpp
//  QYView
//
//  Created by yinquan on 2024/1/4.
//

#ifndef QYPropertyFinalValue_hpp
#define QYPropertyFinalValue_hpp

#include <stdio.h>
#include <string>
class QYPropertyFinalValue {
public:
    enum Type {
        Null,
        Number,
        String,
        Bool
    };
    
    ~QYPropertyFinalValue();
    QYPropertyFinalValue(double value);
    QYPropertyFinalValue(std::string value);
    QYPropertyFinalValue(bool value);
    double getNumberValue();
    std::string getStringValue();
    bool getBoolValue();

private:
    union {
        double mNumber;
        std::string mString;
        bool mBool;
    };
    Type mType;
};

#endif /* QYPropertyFinalValue_hpp */
