//
//  QYPropertyFinalValue.cpp
//  QYView
//
//  Created by yinquan on 2024/1/4.
//

#include "QYPropertyFinalValue.h"
QYPropertyFinalValue::~QYPropertyFinalValue() {
    
}

QYPropertyFinalValue::QYPropertyFinalValue(double value) {
    mType = QYPropertyFinalValue::Number;
    mNumber = value;
}
QYPropertyFinalValue::QYPropertyFinalValue(std::string value) {
    mType = QYPropertyFinalValue::String;
    mString = value;
}
QYPropertyFinalValue::QYPropertyFinalValue(bool value) {
    mType = QYPropertyFinalValue::Bool;
    mBool = value;
}
double QYPropertyFinalValue::getNumberValue() {
    return mNumber;
}
std::string QYPropertyFinalValue::getStringValue() {
    return mString;
}
bool QYPropertyFinalValue::getBoolValue() {
    return mBool;
}
