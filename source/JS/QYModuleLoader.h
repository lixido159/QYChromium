//
//  QYModuleLoader.hpp
//  QYView
//
//  Created by yinquan on 2023/8/26.
//

#ifndef QYModuleLoader_hpp
#define QYModuleLoader_hpp

#include <stdio.h>
#include "v8.h"

v8::MaybeLocal<v8::Module> loadModule(v8::Local<v8::Context> context, const char *js, const char *fileName);
v8::Local<v8::Value> executeModule(v8::Local<v8::Context> context, v8::Local<v8::Module> mod);
v8::MaybeLocal<v8::Module> resolveModuleCallback(v8::Local<v8::Context> context, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> import_assertions, v8::Local<v8::Module> referrer);
#endif /* QYModuleLoader_hpp */
