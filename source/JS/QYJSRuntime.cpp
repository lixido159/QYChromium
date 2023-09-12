//
//  QYJSRuntime.cpp
//  QYView
//
//  Created by yinquan on 2023/8/19.
//

#include "QYJSRuntime.h"
#include "include/v8-context.h"
#include "include/v8-initialization.h"
#include "include/v8-local-handle.h"
#include "include/v8-primitive.h"
#include "include/v8-script.h"
#include "include/v8-template.h"
#include "include/v8-function.h"
#include "include/v8-container.h"
#include "include/v8-persistent-handle.h"
#include "include/libplatform/libplatform.h"
#include "libplatform/default-platform.h"

#include "QYJSContext.h"
static v8::Isolate *mIsolate;
static std::unique_ptr<v8::Platform> mPlatform;
void initJSRuntime(const char * snapshotDir) {
    v8::V8::InitializeExternalStartupData(snapshotDir);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    mPlatform = std::move(platform);
    v8::V8::InitializePlatform(mPlatform.get());
    v8::V8::Initialize();
    
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
    v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    //先创建一个Isolate，负责堆内存的分配
    mIsolate = v8::Isolate::New(create_params);
//    Just For Test !
//    ExecuteJS(context->ToLocal());
//    QYJSValue *global = context->getGlobal();
//    global->setFunction("qyConsole", [](QYJSContext *context, QYJSValue *paramsValue)->QYJSValue *{
//        return nullptr;
//    });
//
//    context->executeJSFile("/Users/yinquan/Documents/library/Work/QYChromium/js/build/bundle.js");
}

v8::Isolate *getIsolate() {
    return mIsolate;
}
