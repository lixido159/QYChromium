//
//  main.m
//  QYChromiumTest
//
//  Created by yinquan on 2023/8/16.
//

#import <Cocoa/Cocoa.h>
#import <QYView/QYEntry.h>
//int main(int argc, const char * argv[]) {
//    @autoreleasepool {
//        // Setup code that might create autoreleased objects goes here.
//    }
//    NSBundle *viewBundle = [NSBundle bundleWithIdentifier:@"qy.QYView"];
//    //TODO:临时解决，复制snapshot到Framework主目录
//    //V8_USE_EXTERNAL_STARTUP_DATA不知道为啥没有编译进去
//    initJS(viewBundle.resourcePath.UTF8String);
//    return NSApplicationMain(argc, argv);
//}

enum TOKEN_TYPE {
    tok_identifier = -1,//变量，比如number、number.length、number.length()这种
    tok_number = -1,//数字
    tok_str = -1,//字符串'xx'、"xx"
    tok_question = -1,//?
    tok_add = -1,//+
    tok_sub = -1,//-
    tok_mul = -1,//*
    tok_div = -1,// /
    
};

getNextToken() {
    
}

int main(int argc, const char * argv[]) {
    return 0;
}
