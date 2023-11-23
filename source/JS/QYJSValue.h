//
//  QYJSValue.hpp
//  QYView
//
//  Created by yinquan on 2023/8/18.
//

#ifndef QYJSValue_hpp
#define QYJSValue_hpp
#include "v8.h"
#include <stdio.h>
#include "QYJSRuntime.h"


class QYJSContext;
class QYJSValue {
public:
    
    QYJSValue(std::shared_ptr<QYJSContext> jsContext);
    QYJSValue(std::shared_ptr<QYJSContext> jsContext, v8::Local<v8::Value> jsValue);
    QYJSValue(std::shared_ptr<QYJSContext> jsContext, const std::function<QYJSValue *(QYJSContext *, QYJSValue*)>& handler);
    
    QYJSValue(std::shared_ptr<QYJSContext> jsContext, bool value);
    QYJSValue(std::shared_ptr<QYJSContext> jsContext, std::string value);
    QYJSValue(std::shared_ptr<QYJSContext> jsContext, double value);
    
    ~QYJSValue();
    v8::Local<v8::Value> ToLocal();
    v8::Local<v8::Object> ToLocalObject();
    std::shared_ptr<QYJSContext> getContext();
    //args必须是个数组
    QYJSValue *call(QYJSValue *args);
    QYJSValue *call(std::vector<QYJSValue *> args);
    
    QYJSValue *call(std::string funcName, QYJSValue *args);
    QYJSValue *call(std::string funcName, std::vector<QYJSValue *> args);

public:
    int length();
    bool has(const char *key);
    bool has(int index);
    QYJSValue *getValue(int index);
    QYJSValue *getValue(const char *key);
    QYJSValue *getValue(std::string key);
    void setValue(const char *key, QYJSValue *value);
    void setValue(const char *key, v8::Local<v8::Value> value);
    void setValue(int index, QYJSValue *value);
    void setValue(int index, v8::Local<v8::Value> value);
    
    std::string toString();
    double toNumber();
    int32_t toInt32();
    uint32_t toUint32();
    bool toBoolean();
public:
    bool isNull();
    bool isUndefined();
    bool isNullOrUndefined();
    bool isTrue();
    bool isFalse();
    bool isString();
    bool isFunction();
    bool isArray();
    bool isObject();
    bool isBigInt();
    bool isBoolean();
    bool isNumber();
    bool isInt32();
    bool isUint32();
    //TODO: Value里的判断太多了，就先加这些吧
public:
    void setFunction(const char *name, const std::function<QYJSValue *(QYJSContext *, QYJSValue*)>& handler);
private:
    v8::Global<v8::Value> mJsValue;
    std::shared_ptr<QYJSContext> mJsContext;
};





#endif /* QYJSValue_hpp */
