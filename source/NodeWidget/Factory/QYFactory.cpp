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
#include "QYIfDomNodeCreatorItem.h"
#include "QYCommonDomNodeCreatorItem.h"

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



std::shared_ptr<QYBaseDomNode> createDomNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYBaseNodeInfo> info, std::shared_ptr<QYPageCompContext> context) {
    std::shared_ptr<QYBaseDomNode> domNode;
    if (info->name.compare("view") == 0 ||
        info->name.compare("image") == 0 ||
        info->name.compare("text") == 0) {
        domNode = std::make_shared<QYBaseDomNode>(pageInfo, info, context);
    } else {
        std::shared_ptr<QYBaseNodeInfo> compInfo = pageInfo->componentsMap[info->name];
        info->addChildNodeInfo(compInfo);
        domNode = std::make_shared<QYComponentDomNode>(pageInfo, info, context);
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
    //if elif else节点
    std::vector<std::shared_ptr<QYBaseNodeInfo>> ifNodeInfoList;
    std::vector<std::shared_ptr<IQYDomNodeCreatorItem>> retItemList;
    std::shared_ptr<QYBaseNodeInfo> ifNodeInfo;
    for (std::shared_ptr<QYBaseNodeInfo> nodeInfo : childInfos) {
        NodeCreatorItemType itemType = getNodeCreatorItemType(nodeInfo);
        if (itemType == NodeCreatorItemType::IF) {
            //前面已经有if else节点
            if (ifNodeInfo) {
                retItemList.push_back(std::make_shared<QYIfDomNodeCreatorItem>(ifNodeInfoList));
                ifNodeInfoList.clear();
            }
            ifNodeInfo = nodeInfo;
            ifNodeInfoList.push_back(nodeInfo);
        } else if (itemType == NodeCreatorItemType::ELIF){
            if (!ifNodeInfo) {
                throw "NO qy:if matchs qy:elif";
            }
            ifNodeInfoList.push_back(nodeInfo);
        } else if (itemType == NodeCreatorItemType::ELSE){
            if (!ifNodeInfo) {
                throw "NO qy:if matchs qy:else";
            }
            ifNodeInfoList.push_back(nodeInfo);
            retItemList.push_back(std::make_shared<QYIfDomNodeCreatorItem>(ifNodeInfoList));
            ifNodeInfoList.clear();
            ifNodeInfo.reset();
        } else if (itemType == NodeCreatorItemType::FOR) {
            
        } else if (itemType == NodeCreatorItemType::COMMON) {
            retItemList.push_back(std::make_shared<QYCommonDomNodeCreatorItem>(nodeInfo));
        }
    }
    //遍历结束
    if (ifNodeInfo) {
        retItemList.push_back(std::make_shared<QYIfDomNodeCreatorItem>(ifNodeInfoList));
    }
    
    return retItemList;
}

