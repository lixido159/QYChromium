//
//  QYCommonDomNodeCreatorItem.cpp
//  QYView
//
//  Created by yinquan on 2024/1/12.
//

#include "QYCommonDomNodeCreatorItem.h"

QYCommonDomNodeCreatorItem::QYCommonDomNodeCreatorItem(std::shared_ptr<QYBaseNodeInfo> nodeInfo):mNodeInfo(nodeInfo) {
    
}

std::shared_ptr<QYBaseDomNode> QYCommonDomNodeCreatorItem::createNode(std::shared_ptr<QYPageInfo> pageInfo, std::shared_ptr<QYPageCompContext> context) {
    return std::make_shared<QYBaseDomNode>(pageInfo, mNodeInfo, context);
}
