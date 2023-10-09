//
//  QYJSContext.hpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#ifndef QYJSContext_hpp
#define QYJSContext_hpp

#include <stdio.h>
#include "QYJSValue.h"
#include "QYJSRuntime.h"
#include "include/v8-context.h"
#include "include/v8-persistent-handle.h"

#define JSQYVar "qyNative"

class QYJSContext {
public:
    QYJSContext();
    ~QYJSContext();
public:
    v8::Local<v8::Context> ToLocal();
    void setGlobalJSValue(QYJSValue *value, const char *name);
    QYJSValue *newObject();
    QYJSValue *getGlobal();
    QYJSValue *executeJS(const char *js, const char *fileName="tmp");
    QYJSValue *executeJSFile(const char *name);
private:
private:
#pragma mark - 注册全局对象：console等
    //注册一个全局对象，js环境中可以直接调用
    void registerContextGlobalObject();
    QYJSValue *createGlobalConsoleObject();
    
private:
    v8::Persistent<v8::Context> mContext;
    
    
};

#endif /* QYJSContext_hpp */
