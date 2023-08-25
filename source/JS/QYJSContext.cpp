//
//  QYJSContext.cpp
//  QYView
//
//  Created by yinquan on 2023/8/17.
//

#include "QYJSContext.h"
#include "include/v8-context.h"
#include <iostream>
#include <fstream>
#include <string>
QYJSContext::QYJSContext() {
    v8::Isolate::Scope isolateScope(getIsolate());
    v8::HandleScope handleScope(getIsolate());
    v8::Local<v8::Context> context = v8::Context::New(getIsolate());
    mContext.Reset(getIsolate() ,v8::Persistent<v8::Context>(getIsolate(), context));
    registerContextGlobalObject();
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
QYJSValue *QYJSContext::executeJS(const char *js) {
    ExecuteJS(ToLocal());
    v8::Local<v8::String> source = v8::String::NewFromUtf8(getIsolate(), js).ToLocalChecked();
    v8::Local<v8::Script> script = v8::Script::Compile(contextLocal, source).ToLocalChecked();
    v8::Local<v8::Value> result = script->Run(contextLocal).ToLocalChecked();
    return nullptr;
}

std::string readFile(const char *fileName) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));
        file.close();
        return content;
    } else {
        std::cout << "Unable to open file" << std::endl;
        return "";
    }
}

QYJSValue *QYJSContext::executeJSFile(const char *name) {
    return executeJS(readFile(name).c_str());
}


