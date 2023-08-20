//
//  QYJSRuntime.hpp
//  QYView
//
//  Created by 全寅 on 2023/8/19.
//

#ifndef QYJSRuntime_hpp
#define QYJSRuntime_hpp
#include "include/v8-isolate.h"

#include <stdio.h>

#define ExecuteJS_RetValue(contextLocal)\
v8::Isolate *isolate = getIsolate();\
v8::Isolate::Scope isolateScope(isolate);\
v8::EscapableHandleScope escapeHandleScope(isolate);\
v8::Context::Scope contextScope(contextLocal);\


#define ExecuteJS(contextLocal)\
v8::Isolate *isolate = getIsolate();\
v8::Isolate::Scope isolateScope(isolate);\
v8::HandleScope handleScope(isolate);\
v8::Context::Scope contextScope(contextLocal);\


void initJSRuntime(const char * snapshotDir);
v8::Isolate *getIsolate();

#endif /* QYJSRuntime_hpp */
