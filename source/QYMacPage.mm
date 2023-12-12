//
//  QYMacPage.m
//  QYView
//
//  Created by yinquan on 2023/12/12.
//

#import "QYMacPage.h"
#include "QYPage.h"
#include <memory>
#include <QYFileInfo/QYPageSerializer.h>
#include "QYJSRuntime.h"
@interface QYMacPage() {
    std::unique_ptr<QYPage> page;
}
@property(nonatomic, strong) NSString *pagePath;
@end

@implementation QYMacPage
- (instancetype)initWithPageName:(NSString *)pageName {
    self = [super init];
    if (self) {
        initJSRuntime([NSBundle bundleForClass:[QYMacPage class]].resourcePath.UTF8String);
        NSString *bundleResourcesPath = [NSBundle mainBundle].resourcePath;
        self.pagePath = [NSString stringWithFormat:@"%@/output/%@", bundleResourcesPath, pageName];
        std::shared_ptr<QYPageInfo> pageInfo = deserializePageInfo([self.pagePath UTF8String]);
        page = std::make_unique<QYPage>(pageInfo);
        page->init();
    }
    return self;

}

-(NSView *)getView {
    return (__bridge NSView *)page->getNativeView();
}
@end
