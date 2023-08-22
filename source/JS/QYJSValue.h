//
//  QYJSValue.hpp
//  QYView
//
//  Created by yinquan on 2023/8/18.
//

#ifndef QYJSValue_hpp
#define QYJSValue_hpp
#include "v8.h"
#include "include/v8-persistent-handle.h"
#include "include/v8-isolate.h"
#include <stdio.h>
#include "QYJSRuntime.h"


class QYJSContext;
class QYJSValue {
public:
    QYJSValue(v8::Isolate *isolate, QYJSContext *jsContext, v8::Local<v8::Value> jsValue);
    v8::Local<v8::Value> ToLocal();
    v8::Local<v8::Object> ToLocalObject();
    
    void setFunction(const char *name, const std::function<QYJSValue *(QYJSContext *, QYJSValue*)>& handler);
private:
    ~QYJSValue();
    v8::Persistent<v8::Value> mJsValue;
    QYJSContext *mJsContext  = nullptr;
};





#endif /* QYJSValue_hpp */
