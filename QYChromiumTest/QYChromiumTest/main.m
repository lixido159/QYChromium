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

//#include "QYExpressionParser.h"
//
//#include <string>




//void printNumber(char *src) {
//    QYExpressionParser parser(src);
//    QYExpression *exp = parser.parseExp();
//    printf("%s = %lf\n", src, exp->getNumberValue());
//}
//
//void testNumberOpt() {
//    printNumber(" 0 ");
//    printNumber("  1 + 2 ");
//    printNumber("  1 - 2 ");
//    printNumber("  99 * 100 ");
//    printNumber("  99 /3 ");
//    printNumber(" 1+2 * 3 + 4 /2 + (3 * 6)/2  ");
//}
//
//void testQuestion() {
//
//}
//
//
//int main(int argc, const char * argv[]) {
//    testNumberOpt();
//    return 0;
//}
