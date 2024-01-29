//
//  QYExpResult.cpp
//  QYView
//
//  Created by yinquan on 2024/1/23.
//

#include "QYExpResult.h"

QYExpResult::QYExpResult() {
    
}

QYExpResult::QYExpResult(QYExpResultType type, std::string string): mType(type), mString(string)  {
    
}

QYExpResult::QYExpResult(QYExpResultType type, double number): mType(type), mNumber(number) {
    
}

QYExpResult::QYExpResult(QYExpResultType type, bool boolean): mType(type), mBoolean(boolean) {
    
}

QYExpResultType QYExpResult::getType() {
    return mType;
}
std::string QYExpResult::getString() {
    return mString;
}
double QYExpResult::getNumber() {
    if (mType == QYExpResultType::Boolean) {
        return mBoolean ? 0 : 1;
    } else if (mType == QYExpResultType::Number) {
        return mNumber;
    } else if (mType == QYExpResultType::String) {
        return std::stod(mString);
    }
    return 0;
}
bool QYExpResult::getBoolean() {
    if (mType == QYExpResultType::Boolean) {
        return mBoolean;
    } else if (mType == QYExpResultType::Number) {
        return mNumber > 0;
    } else if (mType == QYExpResultType::String) {
        return mString.length() > 0;
    }
    return false;
}

bool QYExpResult::isString() {
    return mType == QYExpResultType::String;
}
bool QYExpResult::isNumber() {
    return mType == QYExpResultType::Number;
}
bool QYExpResult::isBoolean() {
    return mType == QYExpResultType::Boolean;
}

bool QYExpResult::isNone() {
    return mType == QYExpResultType::None;
}
