//
//  QYEntry.m
//  QYView
//
//  Created by yinquan on 2023/8/16.
//

#include "QYXmlParser.h"
#include "QYBaseWidget.h"
//#include "src/common/globals.h"
#include "QYTest.h"
#include "QYJSRuntime.h"
extern "C" {
#import "QYEntry.h"
}
void *parseHTML(char *html) {
    return parse(html);
}

void initJS(const char * snapshotDir) {
    initJSRuntime(snapshotDir);
}
