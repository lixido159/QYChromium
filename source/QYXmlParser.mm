//
//  XML.m
//  MacTerminal
//
//  Created by yinquan on 2023/6/11.
//

#import "QYXmlParser.h"
#import <libxml/tree.h>
#import <libxml/parser.h>

#import "QYBaseNodeInfo.h"
#import "QYPage.h"
#import "fileUtil.h"
#define TOCHAR (char *)

//
void printProperties(QYBaseNodeInfo *info) {
    std::map<std::string, std::string>::iterator iter;
    for (iter = info->properties.begin(); iter != info->properties.end(); iter++) {
        printf("节点名：%s  属性名：%s 属性值：%s\n", info->name.c_str(), iter->first.c_str(), iter->second.c_str());
    }
}

void printNodeInfoTree(QYBaseNodeInfo *info) {
    if (info) {
        printProperties(info);
        for (QYBaseNodeInfo *child : info->childNodeInfoList )  {
            printNodeInfoTree(child);
        }
    }
}

//xmlNode转化为QYBaseNodeInfo
QYBaseNodeInfo *toNodeInfo(xmlNodePtr xmlNode) {
    QYBaseNodeInfo *info = new QYBaseNodeInfo();
    info->name = TOCHAR xmlNode->name;
    xmlAttr *attr = xmlNode->properties;
    while(attr) {
        info->properties.insert(std::pair(TOCHAR attr->name, TOCHAR xmlGetProp(xmlNode, attr->name)));
        attr = attr->next;
    }
    xmlNodePtr childXmlNode = xmlNode->children;
    while(childXmlNode) {
        if (childXmlNode->type == XML_ELEMENT_NODE) {
            info->addChildNodeInfo(toNodeInfo(childXmlNode));
        }
        childXmlNode = childXmlNode->next;
    }
    return info;
    
}

QYBaseNodeInfo * parseFileToNodeInfo(const char *htmlFile) {
    xmlDocPtr xmlPtr = xmlReadFile(htmlFile, "UTF-8", XML_PARSE_RECOVER);
    if (!xmlPtr) {
        printf("%s 文件打开失败\n", htmlFile);
        return nullptr;
    }
    
    xmlNodePtr xmlRoot = xmlDocGetRootElement (xmlPtr);
    QYBaseNodeInfo *info = toNodeInfo(xmlRoot);
    xmlFreeDoc(xmlPtr);
    xmlCleanupParser();
    return info;
}

void* parse(const char *htmlFile, const char *jsFile) {
    std::string jsStr = readFile(jsFile);
    QYBaseNodeInfo *info = parseFileToNodeInfo(htmlFile);
    QYBaseDomNode *rootNode = new QYBaseDomNode(info);
    QYPage *page = new QYPage(rootNode, jsStr);
    page->init();
//    printNodeInfoTree(info);

    return page->getRootNode()->getNativeView();
}
