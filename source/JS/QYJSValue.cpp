//
//  QYJSValue.cpp
//  QYView
//
//  Created by yinquan on 2023/8/18.
//

#include "QYJSValue.h"
#include "QYJSContext.h"
#include "QYFunction.h"
#include "include/v8-function.h"

void commonFunction(const v8::FunctionCallbackInfo<v8::Value>& info) {
    ExecuteJS(info.GetIsolate()->GetCurrentContext());
    v8::Local<v8::Value> functionData = info.Data();
    v8::Local<v8::External> externalData = v8::Local<v8::External>::Cast(functionData);
    QYFunction *function = (QYFunction *)(externalData->Value());
    QYJSValue *paramValue = new QYJSValue(info.GetIsolate(), function->jsContext, info.This());
    QYJSValue *retVal = function->func(function->jsContext, paramValue);
    if (retVal == nullptr) {
        info.GetReturnValue().SetUndefined();
    } else {
        info.GetReturnValue().Set(retVal->ToLocal());
    }
    

}

QYJSValue::QYJSValue(v8::Isolate *isolate, QYJSContext *jsContext, v8::Local<v8::Value> jsValue) {
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);
    mJsContext = jsContext;
    mJsValue.Reset(isolate, jsValue);
    mIsolate = isolate;
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
    QYFunction *function = new QYFunction();
    function->func = handler;
    function->jsContext = mJsContext;
    
    v8::Local<v8::Object> object = ToLocalObject();
    v8::Local<v8::External> external = v8::External::New(isolate, (void *)(function));
    object->Set(contextLocal, v8::String::NewFromUtf8(getIsolate(), name).ToLocalChecked(), v8::Function::New(contextLocal, commonFunction, external).ToLocalChecked());
}


#pragma mark - Something
int QYJSValue::length() {
    return 0;
}

QYJSValue* QYJSValue::getValueAt(int index) {
    ExecuteJS(mJsContext->ToLocal());
    if (!isObject()) {
        return nullptr;
    }
    v8::Local<v8::Object> object = ToLocalObject();
    v8::Local<v8::Value> indexValue = object->Get(contextLocal, index).ToLocalChecked();
    if (indexValue.IsEmpty()) {
        return nullptr;
    }
    return new QYJSValue(mIsolate, mJsContext, indexValue);
}

#pragma mark - Do Something

char* QYJSValue::toString() {
    ExecuteJS(mJsContext->ToLocal());
    v8::MaybeLocal<v8::String> strLocal = ToLocal()->ToString(mJsContext->ToLocal());
    v8::String::Utf8Value retVal(mIsolate, strLocal.ToLocalChecked());
    return *retVal;
}
double QYJSValue::toNumber() {
    ExecuteJS(mJsContext->ToLocal());
    v8::Local<v8::Number> retValLocal = ToLocal()->ToNumber(mJsContext->ToLocal()).ToLocalChecked();
    return retValLocal->Value();
}
int32_t QYJSValue::toInt32() {
    ExecuteJS(mJsContext->ToLocal());
    v8::Local<v8::Int32> retValLocal = ToLocal()->ToInt32(mJsContext->ToLocal()).ToLocalChecked();
    return retValLocal->Value();
}
uint32_t QYJSValue::toUint32() {
    ExecuteJS(mJsContext->ToLocal());
    v8::Local<v8::Uint32> retValLocal = ToLocal()->ToUint32(mJsContext->ToLocal()).ToLocalChecked();
    return retValLocal->Value();
}
bool QYJSValue::toBoolean() {
    ExecuteJS(mJsContext->ToLocal());
    v8::Local<v8::Boolean> retValLocal = ToLocal()->ToBoolean(mIsolate);
    return retValLocal->Value();
}
#pragma mark - Is Something
bool QYJSValue::isNull() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsNull();
}
bool QYJSValue::isUndefined() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsUndefined();
}
bool QYJSValue::isNullOrUndefined() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsNullOrUndefined();
}
bool QYJSValue::isTrue() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsTrue();
}
bool QYJSValue::isFalse() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsFalse();
}
bool QYJSValue::isString() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsString();
}
bool QYJSValue::isFunction() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsFunction();
}
bool QYJSValue::isArray() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsArray();
}
bool QYJSValue::isObject() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsObject();
}
bool QYJSValue::isBigInt() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsBigInt();
}
bool QYJSValue::isBoolean() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsBoolean();
}
bool QYJSValue::isNumber() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsNumber();
}
bool QYJSValue::isInt32() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsInt32();
}
bool QYJSValue::isUint32() {
    ExecuteJS(mJsContext->ToLocal());
    return ToLocal()->IsUint32();
}



