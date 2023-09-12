//
//  QYModuleLoader.cpp
//  QYView
//
//  Created by yinquan on 2023/8/26.
//


//参考自：https://gist.github.com/surusek/4c05e4dcac6b82d18a1a28e6742fc23e
#include "QYModuleLoader.h"
#include "QYJSRuntime.h"
#include "fileUtil.h"


v8::MaybeLocal<v8::Module> loadModule(v8::Local<v8::Context> context, const char *js, const char *fileName) {
    ExecuteJS_RetValue(context);
    v8::Local<v8::String> str = strToV8(js);
    v8::ScriptOrigin origin(isolate, strToV8(fileName), 0, 0, false, -1, v8::Local<v8::Value>(), false, false, true);
    v8::ScriptCompiler::Source source(str, origin);
    v8::MaybeLocal<v8::Module> mod = v8::ScriptCompiler::CompileModule(isolate, &source);
    return escapeHandleScope.EscapeMaybe(mod);
}

v8::Local<v8::Value> executeModule(v8::Local<v8::Context> context, v8::Local<v8::Module> mod) {
    ExecuteJS_RetValue(context);
    //加载模块，里面如果依赖了其他模块，会调用resolveModuleCallback
    bool success = mod->InstantiateModule(contextLocal, resolveModuleCallback).ToChecked();;
    if (!success) {
        return v8::Local<v8::Value>();
    }
    //执行代码
    v8::Local<v8::Value>result = mod->Evaluate(contextLocal).ToLocalChecked();
    return escapeHandleScope.Escape(result);
}

v8::MaybeLocal<v8::Module> resolveModuleCallback(v8::Local<v8::Context> context, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> import_assertions, v8::Local<v8::Module> referrer) {
    ExecuteJS_RetValue(context);
    v8::String::Utf8Value str(context->GetIsolate(), specifier);
    return escapeHandleScope.EscapeMaybe(loadModule(context, readFile(*str).c_str(), *str));
}



