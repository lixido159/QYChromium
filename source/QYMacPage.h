//
//  QYMacPage.h
//  QYView
//
//  Created by yinquan on 2023/12/12.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface QYMacPage : NSObject
- (instancetype)initWithPageName:(NSString *)pageName;
-(NSView *)getView;
@end

NS_ASSUME_NONNULL_END
