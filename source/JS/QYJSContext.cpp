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


v8::Local<v8::Context> QYJSContext::ToLocal(){
    v8::Isolate *isolate = getIsolate();
    v8::Isolate::Scope isolateScope(isolate);
    v8::EscapableHandleScope escapeHandleScope(isolate);
    v8::Local<v8::Context> contextLocal = v8::Local<v8::Context>::New(getIsolate(), mContext);
    v8::Context::Scope contextScope(contextLocal);
    return escapeHandleScope.Escape(contextLocal);
}

void QYJSContext::setGlobalJSValue(QYJSValue *value, const char *name) {
    ExecuteJS(ToLocal());
    v8::Local<v8::Object> global = contextLocal->Global();
    global->Set(contextLocal, v8::String::NewFromUtf8(isolate, name).ToLocalChecked(), value->ToLocal());
}


QYJSValue *QYJSContext::newObject() {
    ExecuteJS(ToLocal());
    return new QYJSValue(getIsolate(), v8::Object::New(getIsolate()));
}

void QYJSContext::registerContextGlobalObject() {
    ExecuteJS(ToLocal());
    QYJSValue *consoleObj = createGlobalConsoleObject();
    setGlobalJSValue(consoleObj, "console");
}

QYJSValue *QYJSContext::createGlobalConsoleObject() {
    QYJSValue *jsValue = newObject();
    jsValue->
}
