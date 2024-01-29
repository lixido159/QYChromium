//
//  QYExpResult.hpp
//  QYView
//
//  Created by yinquan on 2024/1/23.
//

#ifndef QYExpResult_hpp
#define QYExpResult_hpp

#include <stdio.h>
#include <string>
enum class QYExpResultType {
    None,
    Number,
    String,
    Boolean,
    Object,
};
class QYExpResult {
public:
    

    QYExpResult();
    QYExpResult(QYExpResultType type, std::string string);
    QYExpResult(QYExpResultType type, double number);
    QYExpResult(QYExpResultType type, bool boolean);
    
    
    QYExpResultType getType();
    std::string getString();
    double getNumber();
    bool getBoolean();
    bool isString();
    bool isNumber();
    bool isBoolean();
    bool isNone();
private:
    QYExpResultType mType = QYExpResultType::None;
    std::string mString = "";
    double mNumber = 0;
    bool mBoolean = false;
};


#endif /* QYExpResult_hpp */
