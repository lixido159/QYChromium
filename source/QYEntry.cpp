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
void *parseHTML(const char *htmlFile, const char *jsFile) {
    return parse(htmlFile, jsFile);
}

void initJS(const char * snapshotDir) {
    initJSRuntime(snapshotDir);
}
