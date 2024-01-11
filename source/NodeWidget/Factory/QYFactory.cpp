//
//  QYFactory.cpp
//  
//
//  Created by yinquan on 2023/7/2.
//

#include "QYFactory.h"
#include "QYBaseView.h"
#include "QYImageView.h"
#include "QYTextView.h"
#include "QYBaseCustomView.h"
#include "QYBaseCustomImageView.h"
#include "QYBaseCustomTextView.h"
#include "QYComponentDomNode.h"
enum class NodeCreatorItemType {
    COMMON,
    IF,
    ELIF,
    ELSE,
    FOR
};


extern QYBaseNodeInfo * parseFileToNodeInfo(const char *htmlFile);
IQYBaseView *createViewWithType(std::string type) {
    IQYBaseView *view;
    if (type.compare("view") == 0) {
        view = new QYBaseView;
    } else if(type.compare("image") == 0) {
        view = new QYImageView;
    } else if (type.compare("text") == 0){//view
        view = new QYTextView;
    } else {
        view = new QYBaseView;
    }
    return view;
}



QYBaseDomNode *createDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context) {
    QYBaseDomNode *domNode;
    if (info->name.compare("view") == 0 ||
        info->name.compare("image") == 0 ||
        info->name.compare("text") == 0) {
        domNode = new QYBaseDomNode(pageInfo, info, context);
    } else {
        std::shared_ptr<QYBaseNodeInfo> compInfo = pageInfo->componentsMap[info->name];
        info->addChildNodeInfo(compInfo);
        domNode = new QYComponentDomNode(pageInfo, info, context);
    }
    return domNode;
};

NodeCreatorItemType getNodeCreatorItemType(std::shared_ptr<QYBaseNodeInfo> info) {
    std::map<std::string, std::string>::iterator end;
    if (info->properties.find("qy:if") != end) {
        return NodeCreatorItemType::IF;
    } else if (info->properties.find("qy:elif") != end) {
        return NodeCreatorItemType::ELIF;
    } else if (info->properties.find("qy:else") != end) {
        return NodeCreatorItemType::ELSE;
    } else if (info->properties.find("qy:for") != end) {
        return NodeCreatorItemType::FOR;
    } else {
        return NodeCreatorItemType::COMMON;
    }
}


std::vector<std::shared_ptr<IQYDomNodeCreatorItem>> createDomNodeCreatorItems(std::vector<std::shared_ptr<QYBaseNodeInfo>> childInfos) {
    for (std::shared_ptr<QYBaseNodeInfo> nodeInfo : childInfos) {
        NodeCreatorItemType itemType = getNodeCreatorItemType(nodeInfo);
        if (itemType)
    }
}

