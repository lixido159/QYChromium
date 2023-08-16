//
//  ViewController.m
//  QYChromiumTest
//
//  Created by 全寅 on 2023/8/16.
//

#import "ViewController.h"
#import <QYView/QYEntry.h>
@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSView *view = (__bridge_transfer NSView *) parseHTML("/Users/yinquan/Documents/library/MyTest/ChromiumMacOS/HTML/qy.html");
    [self.view addSubview:view];
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
