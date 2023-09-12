//
//  ViewController.m
//  QYChromiumTest
//
//  Created by yinquan on 2023/8/16.
//

#import "ViewController.h"
#import <QYView/QYEntry.h>
@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSView *view = (__bridge_transfer NSView *)parseHTML([[NSBundle mainBundle] pathForResource:@"test" ofType:@"html"].UTF8String, @"/Users/yinquan/Documents/library/Work/QYChromium/js/build/bundle.js".UTF8String);
    [self.view addSubview:view];
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
