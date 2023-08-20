//
//  QYJSContext.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYJSContext.h"
#include "include/v8-context.h"

QYJSContext::QYJSContext() {
    v8::Isolate::Scope isolateScope(getIsolate());
    v8::HandleScope handleScope(getIsolate());
    v8::Local<v8::Context> context = v8::Context::New(getIsolate());
    mContext.Reset(getIsolate() ,v8::Persistent<v8::Context>(getIsolate(), context));
}


v8::Local<v8::Context> QYJSContext::getContext(){
    v8::Isolate *isolate = getIsolate();
    v8::Isolate::Scope isolateScope(isolate);
    v8::EscapableHandleScope escapeHandleScope(isolate);
    v8::Local<v8::Context> contextLocal = v8::Local<v8::Context>::New(getIsolate(), mContext);
    v8::Context::Scope contextScope(contextLocal);
    return escapeHandleScope.Escape(contextLocal);
}

void QYJSContext::registerContextGlobalObject() {
    
}
