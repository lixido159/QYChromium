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
    NSView *view = [self.page getView];
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
    view.frame = self.view.bounds;
    [self.view addSubview:view];
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
