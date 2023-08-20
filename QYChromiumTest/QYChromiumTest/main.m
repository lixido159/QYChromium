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
    initJS(viewBundle.resourcePath.UTF8String);
    return NSApplicationMain(argc, argv);
}
