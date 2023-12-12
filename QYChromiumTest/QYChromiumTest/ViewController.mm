//
//  ViewController.m
//  QYChromiumTest
//
//  Created by yinquan on 2023/8/16.
//

#import "ViewController.h"
#import <QYView/QYMacPage.h>
@interface ViewController()
@property(nonatomic, strong) QYMacPage *page;
@end
@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.page = [[QYMacPage alloc] initWithPageName:@"qytest.page"];
//    NSView *view = (__bridge_transfer NSView *)parseHTML([[NSBundle mainBundle] pathForResource:@"index" ofType:@"html"].UTF8String, @"/Users/yinquan/Documents/library/Work/QYChromium/js/build/bundle.js".UTF8String);
    [self.view addSubview:[self.page getView]];
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
