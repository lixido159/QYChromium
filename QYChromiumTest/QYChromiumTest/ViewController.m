//
//  ViewController.m
//  QYChromiumTest
//
//  Created by 全寅 on 2023/8/16.
//

#import "ViewController.h"
#import <QYView/QYXmlParser.h>
@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    QYBaseDomNode *node = parse([[NSBundle mainBundle] pathForResource:@"test" ofType:@"html"].UTF8String);
//    no->nativeView();
    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
