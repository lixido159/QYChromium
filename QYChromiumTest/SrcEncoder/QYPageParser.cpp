//
//  XML.m
//  MacTerminal
//
//  Created by yinquan on 2023/6/11.
//

#include "QYPageParser.h"
#include "fileUtil.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <QYFileInfo/QYPageInfo.h>

#define TOCHAR (char *)

//
void printProperties(std::shared_ptr<QYBaseNodeInfo> info) {
    std::map<std::string, std::string>::iterator iter;
    for (iter = info->properties.begin(); iter != info->properties.end(); iter++) {
        printf("节点名：%s  属性名：%s 属性值：%s\n", info->name.c_str(), iter->first.c_str(), iter->second.c_str());
    }
}

void printNodeInfoTree(std::shared_ptr<QYBaseNodeInfo> info) {
    if (info) {
        printProperties(info);
        for (std::shared_ptr<QYBaseNodeInfo> child : info->childNodeInfoList )  {
            printNodeInfoTree(child);
        }
    }
}

//xmlNode转化为QYBaseNodeInfo
std::shared_ptr<QYBaseNodeInfo> toNodeInfo(xmlNodePtr xmlNode) {
    std::shared_ptr<QYBaseNodeInfo> info = std::make_shared<QYBaseNodeInfo>();
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

std::shared_ptr<QYBaseNodeInfo> parseFileToNodeInfo(const char *htmlFile) {
    xmlDocPtr xmlPtr = xmlReadFile(htmlFile, "UTF-8", XML_PARSE_RECOVER);
    if (!xmlPtr) {
        printf("%s 文件打开失败\n", htmlFile);
        return nullptr;
    }
    
    xmlNodePtr xmlRoot = xmlDocGetRootElement (xmlPtr);
    std::shared_ptr<QYBaseNodeInfo> info = toNodeInfo(xmlRoot);
    xmlFreeDoc(xmlPtr);
    xmlCleanupParser();
    return info;
}

//template <class Archive>
//void serialize(Archive& archive, QYPageInfo& page) {
//    archive(cereal::make_nvp("jsStr", page.jsStr), cereal::make_nvp("componentsMap", page.componentsMap));
//}

std::shared_ptr<QYPageInfo> parsePageInfo(std::string dir) {
    printf("%s \n", dir.c_str());
    std::shared_ptr<QYPageInfo> pageInfo = std::make_shared<QYPageInfo>();
    std::vector<std::string> files;
    traverseDir(dir, ".html", files);
    for (std::vector<std::string>::iterator iter= files.begin(); iter != files.end(); iter++) {
        pageInfo->componentsMap.insert(std::pair(filePathToCompName(*iter, dir), parseFileToNodeInfo((*iter).c_str())));
    }
    return pageInfo;
}
