//
//  QYJSValue.cpp
//  QYView
//
//  Created by yinquan on 2023/8/18.
//

#include "QYJSValue.h"
#include "QYJSContext.h"
#include "include/v8-function.h"

void commonFunction(const v8::FunctionCallbackInfo<v8::Value>& info) {
    
}

QYJSValue::QYJSValue(v8::Isolate *isolate, v8::Local<v8::Object> jsValue) {
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);
    mJsValue.Reset(isolate, jsValue);
}

QYJSValue::~QYJSValue() {
    mJsValue.Reset();
}


v8::Local<v8::Value> QYJSValue::ToLocal() {
    ExecuteJS_RetValue(mJsContext->ToLocal());
    return escapeHandleScope.Escape(v8::Local<v8::Value>::New(getIsolate(), mJsValue));
}

v8::Local<v8::Object> QYJSValue::ToLocalObject() {
    ExecuteJS_RetValue(mJsContext->ToLocal());
    v8::Local<v8::Value> value = ToLocal();
    return escapeHandleScope.Escape(value->ToObject(contextLocal).ToLocalChecked());
}

void QYJSValue::setFunction(const char *name, const std::function<QYJSValue *(QYJSContext *, QYJSValue*)>& handler) {
    ExecuteJS(mJsContext->ToLocal());
    v8::Local<v8::Object> object = ToLocalObject();
    QYFunctionWrapper *wrapper = new QYFunctionWrapper();
    wrapper->handler = handler;
    v8::Local<v8::External> external = v8::External::New(isolate, wrapper);
    object->Set(contextLocal, v8::String::NewFromUtf8(getIsolate(), name), v8::Function::New(contextLocal, commonFunction, external));
}


