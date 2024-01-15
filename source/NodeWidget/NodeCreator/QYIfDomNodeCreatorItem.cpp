//
//  QYIfDomNodeCreatorItem.cpp
//  QYView
//
//  Created by yinquan on 2024/1/12.
//

#include "QYIfDomNodeCreatorItem.h"
#include "QYIfDomNode.h"

QYIfDomNodeCreatorItem::QYIfDomNodeCreatorItem(std::vector<std::shared_ptr<QYBaseNodeInfo>> nodeInfoList):mNodeInfoList(nodeInfoList) {
    
}

std::shared_ptr<QYBaseDomNode> QYIfDomNodeCreatorItem::createNode(std::shared_ptr<QYBaseDomNode> parent, std::shared_ptr<QYPageCompContext> context)  {
    return std::make_shared<QYIfDomNode>(parent, mNodeInfoList, context);
}
