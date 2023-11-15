//
//  QYJSContext.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYJSContext.h"
#include "QYModuleLoader.h"
#include "fileUtil.h"
#include "src/init/v8.h"
QYJSContext::QYJSContext() {
    v8::Platform *p = v8::internal::V8::GetCurrentPlatform();
    p->GetTracingController();
    v8::Isolate::Scope isolateScope(getIsolate());
    v8::HandleScope handleScope(getIsolate());
    v8::Local<v8::Context> context = v8::Context::New(getIsolate());
    mContext.Reset(getIsolate() ,v8::Persistent<v8::Context>(getIsolate(), context));
    registerContextGlobalObject();
}

QYJSContext::~QYJSContext() {
    mContext.Reset();
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
    return new QYJSValue(this, v8::Object::New(getIsolate()));
}

QYJSValue* QYJSContext::getGlobal() {
    ExecuteJS(ToLocal());
    return new QYJSValue(this, contextLocal->Global());
}

void QYJSContext::registerContextGlobalObject() {
    ExecuteJS(ToLocal());
    QYJSValue *consoleObj = createGlobalConsoleObject();
    setGlobalJSValue(consoleObj, "console");
    //注册qy全局对象，后面一些方法都设置到这上面
    setGlobalJSValue(new QYJSValue(this), JSQYVar);
}

QYJSValue *QYJSContext::createGlobalConsoleObject() {
    QYJSValue *jsValue = newObject();
    jsValue->setFunction("log", [](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue *{
        ExecuteJS(context->ToLocal());
        std::string s = paramsValue->getValue(0)->toString();
        printf("打印日志 %s\n", s.c_str());
        return nullptr;
    });
    return jsValue;
}

QYJSValue *QYJSContext::createTimeOutFunction() {
    QYJSValue *jsValue = newObject();
    jsValue->setFunction("log", [](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue *{
        ExecuteJS(context->ToLocal());
        std::string s = paramsValue->getValue(0)->toString();
        printf("打印日志 %s\n", s.c_str());
        return nullptr;
    });
    return jsValue;
}




QYJSValue *QYJSContext::executeJS(const char *js, const char *fileName) {
    ExecuteJS(ToLocal());
    v8::Local<v8::Module> mod = loadModule(contextLocal, js, fileName).ToLocalChecked();
    v8::Local<v8::Value> retValue = executeModule(contextLocal, mod);
    return new QYJSValue(this, retValue);
}



QYJSValue *QYJSContext::executeJSFile(const char *name) {
    return executeJS(readFile(name).c_str(), name);
}


