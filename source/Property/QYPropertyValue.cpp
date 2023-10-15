//
//  QYPropertyValue.cpp
//  QYView
//
//  Created by yinquan on 2023/10/11.
//

#include "QYPropertyValue.h"
#include <regex>
#include "QYExpressionParser.h"
QYPropertyValue::QYPropertyValue(std::string key, std::string src):mKey(key), mSrc(src) {
    mExp = parseSrc(src);
}

QYExpression *QYPropertyValue::parseSrc(std::string src) {
    size_t start = src.find("{");
    size_t end = src.find("}");
    //不是胡子语法，固定值
    if (start == std::string::npos && end == std::string::npos) {
        std::unique_ptr<QYExpressionParser> expParser = std::make_unique<QYExpressionParser>(src);
        return expParser->parseExp();
    }
    //是胡子语法
    else if (start != std::string::npos && end != std::string::npos) {
        std::string readSrc = src.substr(start+1, end-start-1);
        std::unique_ptr<QYExpressionParser> expParser = std::make_unique<QYExpressionParser>(readSrc);
        return expParser->parseExp();
    }
    else {
        throw "胡子语法解析失败";
    }
}

double QYPropertyValue::getNumberValue() {
    return mExp->getNumberValue();
}

std::string QYPropertyValue::getStringValue() {
    return mExp->getStringValue();
}

bool QYPropertyValue::getBoolValue() {
    return mExp->getBoolValue();
}

std::string QYPropertyValue::getKey() {
    return mKey;
}
