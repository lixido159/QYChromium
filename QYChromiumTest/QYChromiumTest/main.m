//
//  main.m
//  QYChromiumTest
//
//  Created by yinquan on 2023/8/16.
//

#import <Cocoa/Cocoa.h>
#import <QYView/QYEntry.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
    }
    NSBundle *viewBundle = [NSBundle bundleWithIdentifier:@"qy.QYView"];
    //TODO:临时解决，复制snapshot到Framework主目录
    //V8_USE_EXTERNAL_STARTUP_DATA不知道为啥没有编译进去
    initJS(viewBundle.resourcePath.UTF8String);
    return NSApplicationMain(argc, argv);
}
