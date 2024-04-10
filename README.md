# 大前端Demo

## 介绍
- 该工程是一个从零实现跨平台大前端项目。
- 使用v8内核，UI使用NSView，布局使用yoga


## 如何运行
- 打开`QYChromiumTest.xcodeproj`，执行QYChromiumTest target就能运行。
```
    //加载页面
    [[QYMacPage alloc] initWithPageName:@"qytest.page"];
    //获取view就能展示
    NSView *view = [self.page getView];
```

### JS代码
- 这里使用的TypeScript，相关代码在js目录下。
- 可以直接修改js/src/pages/qytest里的文件。
- 目录结构：
  - build：保留webpack打包后的ts文件产物；
  - develop.sh：运行webpack合并ts文件，执行./SrcEncoder；
  - output：SrcEncoder打包产物；
  - src：业务代码；    
  - SrcEncoder：将html和ts文件转换成页面信息(C++对象)，然后保存，启动时程序直接加载，减少加载时间；

## 已支持的功能
1. html解析成view节点；
2. js代码执行；
3. 基本属性支持：width、height、background-color等；
4. 事件响应：bindmouseup；
5. 支持子页面，如`<qycomp-test/>`；
6. 支持flex布局，使用yoga支持；
7. 支持if-else属性；
8. 支持属性的胡子语法，表达式解析。`qy:if="{{ (number % 3 == 0) }}"`；
9. 提前解析html和ts，启动直接加载解析好的布局文件；
10. 支持console.log方法；

 
