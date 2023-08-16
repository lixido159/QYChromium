//
//  QYEntry.m
//  QYView
//
//  Created by 全寅 on 2023/8/16.
//

#include "QYXmlParser.h"
#include "QYBaseWidget.h"
//#include "src/common/globals.h"
#include "QYTest.h"
extern "C" {
#import "QYEntry.h"
}
void *parseHTML(char *html) {
    QYBaseDomNode *domNode = parse(html);
    return domNode->nativeView();
}
