//
//  QYTest.cpp
//  libEVO
//
//  Created by yinquan on 2023/7/16.
//

#include "QYTest.h"
#include "include/v8-context.h"
#include "include/v8-initialization.h"
#include "include/v8-isolate.h"
#include "include/v8-local-handle.h"
#include "include/v8-primitive.h"
#include "include/v8-script.h"
#include "include/v8-template.h"
#include "include/v8-function.h"
#include "include/v8-container.h"
#include "include/v8-persistent-handle.h"
#include "include/libplatform/libplatform.h"
#include "libplatform/default-platform.h"


using namespace v8;

void consoleLog(const v8::FunctionCallbackInfo<Value>& info) {
    v8::HandleScope handle_scope(info.GetIsolate());
    Local<String> value = info[0]->ToString(info.GetIsolate()->GetCurrentContext()).ToLocalChecked();
    String::Utf8Value string(info.GetIsolate(), value);
    printf("%s \n", *string);

}

void registerConsoleLog(v8::Isolate *isolate, v8::Local<v8::Context> context) {
    v8::HandleScope handle_scope(isolate);
    Local<Object> console = Object::New(isolate);
    console->Set(context, String::NewFromUtf8Literal(isolate, "log"), Function::New(context, consoleLog).ToLocalChecked());
    context->Global()->Set(context, String::NewFromUtf8Literal(isolate, "console"), console);
}



void executeJS (v8::Isolate *isolate, v8::Local<v8::Context>context) {
    v8::HandleScope handleScope(isolate);
    // Create a string containing the JavaScript source code.
    // 测试console.log、print、add
    v8::Local<v8::String> source =
    v8::String::NewFromUtf8Literal(isolate, "print(\"测试\"); console.log(123123); function add(a, b) {return a+b;}");
    // Compile the source code.
    // MaybeLocal代表一个不确定的Local结果，是对Local的封装。
    //如果一个方法返回MaybeLocal，那可能因为方法抛异常等原因，返回一个空的MaybeLocal
    //如果MaybeLocal空，ToLocalChecked会crash
    v8::Local<v8::Script> script =
    v8::Script::Compile(context, source).ToLocalChecked();

    // Run the script to get the result.
    v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(isolate, result);
}

//print方法
void printMethod(const FunctionCallbackInfo<Value>& info) {
    v8::HandleScope handleScope(info.GetIsolate());
    Local<String> string = info[0]->ToString(info.GetIsolate()->GetCurrentContext()).ToLocalChecked();
    String::Utf8Value str(info.GetIsolate(), string);
    char *s = *str;
    
}

void registerGlobalFunction(v8::Isolate *isolate, v8::Local<v8::Context>context) {
    v8::HandleScope handleScope(isolate);
    context->Global()->Set(context, String::NewFromUtf8(isolate, "print").ToLocalChecked(), Function::New(context, printMethod).ToLocalChecked());
}

//调用JS的add方法
void callJS(v8::Isolate *isolate, v8::Local<v8::Context>context) {
    v8::HandleScope handleScope(isolate);
    Local<Value> value = context->Global()->Get(context, String::NewFromUtf8(isolate, "add").ToLocalChecked()).ToLocalChecked();
    CHECK(value->IsFunction());
    Local<Function> function = value.As<Function>();
    const int argc = 2;
    Local<Value> params[argc] = {Integer::New(isolate, 99), Integer::New(isolate, 32)};
    Local<Value> recv = function->Call(context, context->Global(), argc, params).ToLocalChecked();
    int result = recv->ToInt32(context).ToLocalChecked()->Value();
    printf("%d\n", result);
}


void startTest(int argc, const char * argv[]) {
    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();
    
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
    v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    //先创建一个Isolate，负责堆内存的分配
    v8::Isolate* isolate = v8::Isolate::New(create_params);
    
    isolate->Enter();
    {
        //必须要有handleScope才能
        v8::HandleScope handleScope(isolate);
        // Context代表一个执行js的环境，包括全局变量、函数等，执行js需要一个context，每个context的环境不同
        // 也需要调用->Enter()进入，->Exit()退出，但是Context::Scope的创建和销毁自动完成了这两步。
        v8::Local<v8::Context> context = v8::Context::New(isolate);
        
        // Enter the context for compiling and running the hello world script.
        context->Enter();
        registerGlobalFunction(isolate, context);
        registerConsoleLog(isolate, context);
        executeJS(isolate, context);
        callJS(isolate, context);
        context->Exit();
    }
    
    isolate->Exit();
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::DisposePlatform();
    delete create_params.array_buffer_allocator;

}
