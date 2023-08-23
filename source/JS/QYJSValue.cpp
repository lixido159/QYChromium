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
    QYJSValue *paramValue = new QYJSValue(function->jsContext);
    for (int i = 0; i<info.Length(); i++) {
        paramValue->setValue(i, info[i]);
    }
    QYJSValue *retVal = function->func(function->jsContext, paramValue);
    if (retVal == nullptr) {
        info.GetReturnValue().SetUndefined();
    } else {
        info.GetReturnValue().Set(retVal->ToLocal());
    }
    

}

QYJSValue::QYJSValue(QYJSContext *jsContext, v8::Local<v8::Value> jsValue) {
    ExecuteJS(jsContext->ToLocal());
    mJsContext = jsContext;
    mJsValue.Reset(getIsolate(), jsValue);
}

QYJSValue::QYJSValue(QYJSContext *jsContext) {
    ExecuteJS(jsContext->ToLocal());
    mJsContext = jsContext;
    mJsValue.Reset(getIsolate(), v8::Object::New(getIsolate()));
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

bool QYJSValue::has(const char *key) {
    ExecuteJS(mJsContext->ToLocal());
    if (!isObject()) {
        return false;
    }
    v8::Local<v8::Object> object = ToLocalObject();
    return object->Has(contextLocal, v8::String::NewFromUtf8(isolate, key).ToLocalChecked()).ToChecked();
}

bool QYJSValue::has(int index) {
    ExecuteJS(mJsContext->ToLocal());
    if (!isObject()) {
        return false;
    }
    v8::Local<v8::Object> object = ToLocalObject();
    return object->Has(contextLocal, index).ToChecked();
}


QYJSValue* QYJSValue::getValue(int index) {
    ExecuteJS(mJsContext->ToLocal());
    if (!isObject()) {
        return nullptr;
    }
    v8::Local<v8::Object> object = ToLocalObject();
    v8::Local<v8::Value> retVal = object->Get(contextLocal, index).ToLocalChecked();
    if (retVal.IsEmpty()) {
        return nullptr;
    }
    return new QYJSValue(mJsContext, retVal);
}

QYJSValue* QYJSValue::getValue(const char *key) {
    ExecuteJS(mJsContext->ToLocal());
    if (!isObject()) {
        return nullptr;
    }
    v8::Local<v8::Object> object = ToLocalObject();
    v8::Local<v8::Value> retVal = object->Get(contextLocal, v8::String::NewFromUtf8(isolate, key).ToLocalChecked()).ToLocalChecked();
    if (retVal.IsEmpty()) {
        return nullptr;
    }
    return new QYJSValue(mJsContext, retVal);

}

void QYJSValue::setValue(const char *key, QYJSValue *value) {
    ExecuteJS(mJsContext->ToLocal());
    setValue(key, value->ToLocal());
    
}
void QYJSValue::setValue(const char *key, v8::Local<v8::Value> value) {
    ExecuteJS(mJsContext->ToLocal());
    if (!isObject()) {
        return;
    }
    v8::Local<v8::Object> object = ToLocalObject();
    v8::Local<v8::Value> keyLocal = v8::String::NewFromUtf8(isolate, key).ToLocalChecked();
    object->Set(contextLocal, keyLocal, value);

}
void QYJSValue::setValue(int index, QYJSValue *value) {
    ExecuteJS(mJsContext->ToLocal());
    setValue(index, value->ToLocal());

}
void QYJSValue::setValue(int index, v8::Local<v8::Value> value) {
    ExecuteJS(mJsContext->ToLocal());
    if (!isObject()) {
        return;
    }
    v8::Local<v8::Object> object = ToLocalObject();
    object->Set(contextLocal, index, value);
}


#pragma mark - Do Something

//这里如果直接返回char *，Utf8Value被释放后 char *也会被释放
std::string QYJSValue::toString() {
    ExecuteJS(mJsContext->ToLocal());
    v8::MaybeLocal<v8::String> strLocal = ToLocal()->ToString(mJsContext->ToLocal());
    v8::String::Utf8Value retVal(getIsolate(), strLocal.ToLocalChecked());
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
    v8::Local<v8::Boolean> retValLocal = ToLocal()->ToBoolean(getIsolate());
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



